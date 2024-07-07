package com.example.Child_Safety;


/**
 *    Copyright 2021 The MathWorks, Inc.
 */

import android.content.Context;
import android.text.TextUtils;
import org.json.JSONObject;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.Set;
import java.util.Timer;
import java.util.TimerTask;

public class ThingSpeakRead {
    private static final String SERVER = "https://api.thingspeak.com";
    Hashtable<Integer,FieldInfo> FieldInfoMap = new Hashtable<>();
    String mGenericError = "";
    boolean mAsynctaskStart = false;
    private int channelID;
    private String readAPIKey;
    private LogFragment mLogFragment;

    public ThingSpeakRead(int channelID, String readAPIKey, int field, Context context, double sampleTime) {
        this.channelID = channelID;
        this.readAPIKey = readAPIKey;
        addSampleTime(field, sampleTime);
    }

    void setFieldValue(int field, float value, float responseCode) {
            FieldInfo fieldData = FieldInfoMap.get(field);
            if (fieldData !=null) {
                fieldData.value = value;
                fieldData.ResponseCode = responseCode;
            }
    }

    public int getChannelID() {
        return channelID;
    }

    public void setChannelID(int channelID) {
        this.channelID = channelID;
    }

    public void setReadAPIKey(String readAPIKey) {
        this.readAPIKey = readAPIKey;
    }

    public void addSampleTime(int field, double sampleTime){
        URL Url;
        try {
            if (this.readAPIKey != null)
                Url = new URL(SERVER + "/channels/" + this.channelID + "/fields/"+ field +"/last.json?api_key=" + this.readAPIKey);
            else
                Url = new URL(SERVER + "/channels/" + this.channelID + "/fields/"+ field +"/last.json");
        } catch (MalformedURLException ex) {
            Url = null;
        }
        FieldInfo fieldInfo = new FieldInfo(field, sampleTime, Url);
        FieldInfoMap.put(field, fieldInfo);
    }

    public float[] readData(int channelID, int field) {
        if (field > 0 && field < 9) {
            float[] f = new float[2];
            FieldInfo mFielddata = FieldInfoMap.get(field);
            if (mFielddata != null) {
                f[0] = mFielddata.value;
                f[1] = mFielddata.ResponseCode;
                if (f[1] == HttpURLConnection.HTTP_OK) {
                    updateLogTab("ThingSpeakRead : Success: Read data from ThingSpeak server");
                }
            }
            if (mAsynctaskStart && f[1] == 0 && TextUtils.isEmpty(mGenericError)) {
                updateLogTab("ThingSpeakRead : Error : " + "Channel " + channelID + " does not contain field " + field);
            }
            return f;
        }
        return null;
    }

    public void cancelTimer() {
        Set<Integer> keySet = FieldInfoMap.keySet();
        Iterator<Integer> itr = keySet.iterator();
        while (itr.hasNext()) {
            Integer v = itr.next();
            FieldInfoMap.get(v).cancelTimer();
        }
    }

    private synchronized void updateLogTab(String LogText) {
        if (mLogFragment != null) {
            mLogFragment.updateThingSpeakLogforReadBlock(LogText);
        }
    }

    public void setLogFragment(LogFragment logFragment) {
        this.mLogFragment = logFragment;
    }

    class FieldInfo {
        float value;
        float ResponseCode;
        Timer myTimerTask;
        double sampleTime;
        int field;


        public FieldInfo(int field, double sampleTime, URL mUrl) {
            value = 0;
            ResponseCode = 0;
            this.field = field;
            this.sampleTime = (sampleTime*1000)/2;
            myTimerTask = new Timer();
            myTimerTask.scheduleAtFixedRate(new MyTimerTask(field, mUrl), 0, (long)this.sampleTime);
        }

        public void cancelTimer() {
            if (myTimerTask != null)
                myTimerTask.cancel();
        }
    }

    class MyTimerTask extends TimerTask {
        int field;
        URL mURL;

        public MyTimerTask(int field, URL mURL ) {
            this.field = field;
            this.mURL = mURL;
        }

        public void run() {
            String s = "";
            String inputLine;
            HttpURLConnection conn = null;
            StringBuilder response = new StringBuilder();
            try {
                conn = (HttpURLConnection) mURL.openConnection();
                conn.setDoInput(true);
                conn.setRequestMethod("GET");
                conn.setRequestProperty("Content-Type", "application/json");
                conn.connect();
                mAsynctaskStart = true;
                int v = conn.getResponseCode();
                if (v == HttpURLConnection.HTTP_OK) {
                    InputStreamReader streamReader = new InputStreamReader(conn.getInputStream());
                    BufferedReader reader = new BufferedReader(streamReader);
                    StringBuilder stringBuilder = new StringBuilder();
                    while ((inputLine = reader.readLine()) != null) {
                        stringBuilder.append(inputLine);
                    }
                    reader.close();
                    streamReader.close();
                    String result = stringBuilder.toString();
                    String searchField = "field" + field;
                    if (result.contains(searchField)) {
                        JSONObject jObj = new JSONObject(result);
                        String totalItems = jObj.getString(searchField);
                        if (totalItems != null && !totalItems.equals("null")) {
                            setFieldValue(field, Float.valueOf(totalItems), 200);
                        } else {
                            setFieldValue(field, 0, 0);
                        }
                    }
                } else {
                    setFieldValue(field, 0, v);
                }
                switch (v) {
                    case HttpURLConnection.HTTP_OK:
                        s = "";
                        break;
                    case HttpURLConnection.HTTP_UNAUTHORIZED:
                        s = "ThingSpeakRead : Error : HTTP Error 401: Authentication error.Check your Write API Key  and Channel id.";
                        break;
                    case HttpURLConnection.HTTP_NOT_FOUND:
                        s = "ThingSpeakRead : Error : HTTP Error 404: The page you requested does not exist.Check the URL and redeploy the model.";
                        break;
                    case 429:
                        s = "ThingSpeakRead  : Error : HTTP Error 429: Too many requests made to the server.Increase update interval in the block and redeploy the model.";
                        break;
                    case HttpURLConnection.HTTP_BAD_REQUEST:
                        if (readAPIKey != null)
                            s = "ThingSpeakRead : Error :  Either Channel ID " + channelID + "or ReadAPIkey " + readAPIKey + " is wrong";
                        else
                            s = "ThingSpeakRead : Error :  Channel ID " + channelID + " is wrong";
                        break;
                    default:
                        s = "ThingSpeakRead : Error: An unexpected error has occurred with HTTP response code " + v + ".";
                }
                conn.disconnect();
                conn = null;
            } catch (java.net.UnknownHostException ex) {
                setFieldValue(field,0, 0);
                s = "ThingSpeakRead : Error: Unable to connect to server. Check device network connection, Server IP address and redeploy the model.";
            } catch (java.io.FileNotFoundException ex) {
                setFieldValue(field,0, 0);
                s = "ThingSpeakRead : Error :  Either Channel ID " + channelID + "or ReadAPIkey " + readAPIKey + " is wrong";
            } catch (Exception ex) {
                setFieldValue(field,0, 0);
                s = "ThingSpeakRead : Error : " + ex.getMessage();
            } finally {
                if (conn != null)
                    conn.disconnect();
            }
            if ((!TextUtils.isEmpty(s)) && (!s.equals(mGenericError))) {
                mGenericError = s;
                updateLogTab(s);
            }
        }
    }

}
