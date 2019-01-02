package com.example.zjf.jnithread;

public class ThreadDemo {
	private static final String TAG = "ThreadDemo";

	// Used to load the 'native-lib' library on application startup.
	static {
		System.loadLibrary("native-lib");
	}

	public native void normalThread();

	public native void mutexThread();

	public native void callbackFromC();
	private OnErrorListener onErrorListener;

	public void setOnErrorListener(OnErrorListener onErrorListener) {
		this.onErrorListener = onErrorListener;
	}

	public void onError(int code, String msg){
		if (onErrorListener != null) {
			onErrorListener.OnError(code,msg);
		}
	}

	public interface OnErrorListener{
		void OnError(int code ,String msg);
	}
}
