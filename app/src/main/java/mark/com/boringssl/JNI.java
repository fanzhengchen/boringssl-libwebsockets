package mark.com.boringssl;

/**
 * Created by mark on 17-6-20.
 */

public class JNI {

    public JNI() {
        try {
            System.loadLibrary("native");
        } catch (UnsatisfiedLinkError error) {
            error.printStackTrace();
        }
    }

    public native String stringFromJni();

    public native void connect();

    public native void serviceWebSockets();
}
