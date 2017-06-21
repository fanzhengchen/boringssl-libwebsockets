package mark.com.boringssl;

import android.os.AsyncTask;

/**
 * Created by mark on 17-6-21.
 */

public class Task extends AsyncTask<JNI, Integer, Integer> {

    @Override
    protected void onPostExecute(Integer integer) {
        super.onPostExecute(integer);
    }

    @Override
    protected Integer doInBackground(JNI... params) {
        JNI jni = params[0];
        jni.connect();

        jni.serviceWebSockets();
        return 0;
    }

    @Override
    protected void onPreExecute() {
        super.onPreExecute();
    }
}
