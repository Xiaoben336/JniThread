package com.example.zjf.jnithread;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
	private static final String TAG = "MainActivity";
	private ThreadDemo threadDemo;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		threadDemo = new ThreadDemo();
		threadDemo.setOnErrorListener(new ThreadDemo.OnErrorListener() {
			@Override
			public void OnError(int code, String msg) {
				Log.d(TAG,"code === " + code + "   msg === " +msg);
			}
		});
	}



	public void normal(View view) {
		threadDemo.normalThread();
	}

	public void mutexThread(View view) {
		threadDemo.mutexThread();
	}

	public void callJavaMethod(View view) {
		threadDemo.callbackFromC();
	}
}
