package mark.com.boringssl;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.example.WebSocket;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.


    JNI mJNI = new JNI();
    Task mTask = new Task();


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        System.out.println("fuck");
        TextView tv = (TextView) findViewById(R.id.sample_text);
//        tv.setText(stringFromJNI());
        tv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new Task().execute(mJNI);
            }
        });
    }


}
