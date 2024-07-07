package com.example.Child_Safety;


import android.app.Activity;
import android.os.Bundle;
import androidx.fragment.app.Fragment;
import android.text.TextUtils;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import android.text.method.ScrollingMovementMethod;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class LogFragment extends Fragment {

   private OnFragmentInteractionListener mListener;

   private TextView thingSpeakLog;
   private TextView tcpLog;
   private TextView tcpLogTitle;
   private TextView thingSpeakLogTitle;
   private TextView MQTTLogTitle;
   private TextView MQTTLog;
   private TextView HTTPClientLogTitle;
   private TextView HTTPClientLog;
   private StringBuilder tcpLogBuilder;
   private StringBuilder ThingSpeakLogtext;
   private StringBuilder MqttLogBuilder;
   private StringBuilder HttpClientLogBuilder;
   
   int mThingSpeakReadCount = 0;
   void incrementThingSpeakCounter() {
       mThingSpeakReadCount++;
   }

   void resetThingSpeakCounter() {
       mThingSpeakReadCount = 0;
   }

   int mqttReadSuccessCounter = 0;
   int mqttpostSuccessCounter = 0;
   int httpConnectionSuccessCounter = 0;
   int httpErrorCounter = 0;
   public LogFragment() {}

   public static LogFragment newInstance() {
       LogFragment fragment = new LogFragment();
       Bundle args = new Bundle();
       fragment.setArguments(args);
       return fragment;
   }

   @Override
   public View onCreateView(LayoutInflater inflater, ViewGroup container,
                Bundle savedInstanceState) {
       View rootView = inflater.inflate(R.layout.fragment_log, container, false);
       thingSpeakLog = (TextView)rootView.findViewById(R.id.thingspeaklog);
       tcpLog = (TextView)rootView.findViewById(R.id.tcplog);
       thingSpeakLogTitle = (TextView)rootView.findViewById(R.id.thingspeaklogtitle);
       tcpLogTitle = (TextView)rootView.findViewById(R.id.tcplogtitle);
       thingSpeakLog.setMovementMethod(new ScrollingMovementMethod());
       tcpLog.setMovementMethod(new ScrollingMovementMethod());
       thingSpeakLog.setVisibility((1== 1)? View.VISIBLE : View.GONE);
       thingSpeakLogTitle.setVisibility((1==1)? View.VISIBLE : View.GONE);
       tcpLogTitle.setVisibility((0==1) ? View.VISIBLE : View.GONE);
       tcpLog.setVisibility((0== 1)? View.VISIBLE : View.GONE);
       if (tcpLogBuilder == null)
           tcpLogBuilder = new StringBuilder("");
       if(ThingSpeakLogtext == null)
           ThingSpeakLogtext = new StringBuilder("");
       if (MqttLogBuilder == null)
           MqttLogBuilder = new StringBuilder("");
       if (HttpClientLogBuilder == null)
           HttpClientLogBuilder = new StringBuilder("");
       return rootView;
   }

   @Override
   public void onAttach(Activity activity) {
       super.onAttach(activity);
       try {
           mListener = (OnFragmentInteractionListener) activity;
       } catch (ClassCastException e) {
           throw new ClassCastException(activity.toString()
           + " must implement OnFragmentInteractionListener");
       }
   }

   @Override
   public void onDetach() {
       super.onDetach();
       mListener = null;
   }

   @Override
   public void onStart() {
       super.onStart();
       if (!TextUtils.isEmpty(tcpLogBuilder))
           tcpLog.setText(tcpLogBuilder.toString());
       mListener.onFragmentStart("Log");
   }


   public void updateThingSpeakLogforReadBlock(String newEntry) {
       if(ThingSpeakLogtext == null)
           ThingSpeakLogtext = new StringBuilder("");
       String currentEntries = ThingSpeakLogtext.toString();
       if (newEntry.contains("Error")) {
           resetThingSpeakCounter();
           if(newEntry.contains("not contain field") && currentEntries.contains(newEntry)) {
               return;
           }
       } else if(newEntry.startsWith("ThingSpeakRead : Success: Read data")) {
            incrementThingSpeakCounter();
            newEntry = newEntry + ".(" + mThingSpeakReadCount + ").";
       }
       String timeStamp = new SimpleDateFormat("d MMM yyyy HH:mm:ss.SSS").format(new Date());
       newEntry = newEntry + "" + "\n[" + timeStamp + "]";
       updateLog(newEntry);
   }

   public void updateThingSpeakLogforTalkbackBlocks(String newEntry) {
       if(ThingSpeakLogtext == null)
           ThingSpeakLogtext = new StringBuilder("");
       String currentEntries = ThingSpeakLogtext.toString();
       if (currentEntries.contains(newEntry)) {
               return;
       }
       String timeStamp = new SimpleDateFormat("d MMM yyyy HH:mm:ss.SSS").format(new Date());
       newEntry = newEntry + "" + "\n[" + timeStamp + "]";
       updateLog(newEntry);
   }

   public synchronized void updateLog(String newEntry) {
      if(ThingSpeakLogtext == null)
          ThingSpeakLogtext = new StringBuilder("");
      String currentEntries = ThingSpeakLogtext.toString();
      if (newEntry.startsWith("Success: Data posted") && currentEntries.startsWith("Success: Data posted")) {
          currentEntries = currentEntries.replaceFirst("Success: Data posted to ThingSpeak server(.*?)\\.\n\\[(.*?)\\]", newEntry);
          newEntry = "";
      }
      if (newEntry.startsWith("ThingSpeakRead : Success: Read data") && currentEntries.startsWith("ThingSpeakRead : Success: Read data")) {
          currentEntries = currentEntries.replaceFirst("ThingSpeakRead : Success: Read data from ThingSpeak server(.*?)\\.\n\\[(.*?)\\]", newEntry);
          newEntry = "";
      }
      ThingSpeakLogtext = new StringBuilder(currentEntries);
      if (!newEntry.isEmpty())
          ThingSpeakLogtext.insert(0, newEntry + "\n\n");
      final String ThingSpeakText = ThingSpeakLogtext.toString();
      if (mListener != null)
          getActivity().runOnUiThread(new Runnable() {
     @Override
     public void run() {
         thingSpeakLog.setText(ThingSpeakText);
     }
   });
   }

   public synchronized void updateTCPLog(String errorInfo) {
      if (tcpLogBuilder == null)
         tcpLogBuilder = new StringBuilder("");
      tcpLogBuilder.insert(0, errorInfo);
      final String errorLog = tcpLogBuilder.toString();
      if (mListener != null)
          getActivity().runOnUiThread(new Runnable() {
          @Override
          public void run() {
              tcpLog.setText(errorLog);
          }
       });
   }
}
