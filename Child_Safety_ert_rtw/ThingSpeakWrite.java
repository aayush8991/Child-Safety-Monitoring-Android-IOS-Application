package com.example.Child_Safety;


/**
 *    Copyright 2021 The MathWorks, Inc.
 */

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.UnknownHostException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Hashtable;
import java.util.Set;

public class ThingSpeakWrite {
    private static final int NUM_FIELDS = 8;
    private static final String LOG_TAG = "SHOW_LOGS";
    private static final String SERVER = "https://api.thingspeak.com";
    Hashtable<String, Double> fields = new Hashtable<>();
    JSONObject jsonObject;
    private long lastUpdateTime;
    private int channelID;
    private double updateInterval;
    private String writeAPIKey;
    private int successCount = 1;

    public ThingSpeakWrite() {
        jsonObject = new JSONObject();
        lastUpdateTime = 0;
    }

    public int getChannelID() {
        return channelID;
    }

    public void setChannelID(int channelID) {
        this.channelID = channelID;
    }

    public void setWriteAPIKey(String writeAPIKey) {
        this.writeAPIKey = writeAPIKey;
    }

    public void setUpdateInterval(double updateInterval) {
        this.updateInterval = updateInterval;
    }

    public boolean isSafeToPost() {
        long currentTime = System.currentTimeMillis();
        boolean safe = false;
        if (lastUpdateTime == 0 || ((currentTime - lastUpdateTime) >= 1000 * updateInterval)) {
            lastUpdateTime = currentTime;
            safe = true;
        }
        return safe;
    }

    public void addField(int field, double value) {
        if (field > NUM_FIELDS)
            return;
        fields.put("field" + field, value);
    }

    public void addLocation(double[] location) {
        fields.put("lat", location[0]);
        fields.put("long", location[1]);
        fields.put("elevation", location[2]);
    }

    private void createMessage() throws JSONException {
        jsonObject.put("api_key", this.writeAPIKey);
        Set<String> keys = fields.keySet();
        for (String key : keys) {
            jsonObject.put(key, fields.get(key).toString());
        }
    }

    public String sendPostRequest() {
        HttpURLConnection conn = null;
        StringBuilder response = new StringBuilder();
        boolean postError = true;

        try {
            this.createMessage();

            URL url = new URL(SERVER + "/channels/" + this.channelID + "/feeds.json/");
            conn = (HttpURLConnection) url.openConnection();
            conn.setDoOutput(true);
            conn.setRequestMethod("POST");
            conn.setRequestProperty("Content-Type", "application/json");

            OutputStreamWriter out = new OutputStreamWriter(conn.getOutputStream());
            out.write(jsonObject.toString());
            out.flush();

            switch (conn.getResponseCode()) {
                case 200:
                    postError = false;
                    response.append("ThingSpeakWrite: Success: Data posted to ThingSpeak server.");
                    break;
                case 401:
                    response.append("ThingSpeakWrite: HTTP Error 401: Authentication error.\nCheck your Write API Key and Channel id.");
                    break;
                case 404:
                    response.append("ThingSpeakWrite: HTTP Error 404: The page you requested does not exist.\nCheck the URL and redeploy the model.");
                    break;
                case 429:
                    response.append("ThingSpeakWrite: HTTP Error 429: Too many requests made to the server.\nIncrease update interval in the block and redeploy the model.");
                    break;
                default:
                    response.append("ThingSpeakWrite: Error: An unexpected error has occurred.");
            }
        } catch (Exception ex) {
            if (ex instanceof UnknownHostException)
                response.append("ThingSpeakWrite: Error: Unable to connect to server.\nCheck device network connection, Server IP address and redeploy the model.");
            else if (ex instanceof IOException)
                response.append("ThingSpeakWrite: Error: An IOException occurred while connecting to URL");
            else
                response.append("ThingSpeakWrite: Error: An unexpected error has occurred.");
        } finally {
            if (conn != null) {
                conn.disconnect();
            }
        }

        if (postError) {
            successCount = 1;
        } else {
            response.append(" (" + successCount + ").");
            successCount++;
        }
        String timeStamp = new SimpleDateFormat("d MMM yyyy HH:mm:ss.SSS").format(new Date());
        return response.toString() + "\n[" + timeStamp + "]";
    }
}
