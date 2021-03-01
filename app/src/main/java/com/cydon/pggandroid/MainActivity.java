package com.cydon.pggandroid;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

public class MainActivity extends AppCompatActivity {

    private static final int START_UNITY_PLAYER_INTENT = 392;
    private boolean isUnityLoaded = false;

    static {
        System.loadLibrary("pggandroidnative");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        setContentView(R.layout.activity_main);
        
        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        findViewById(R.id.launch_button).setOnClickListener((View v) -> {
            isUnityLoaded = true;
            initMod();

            Intent startUnityIntent = new Intent(this, UnityPlayerActivity.class)
											.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
            startActivityForResult(startUnityIntent,START_UNITY_PLAYER_INTENT);
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == START_UNITY_PLAYER_INTENT)
            isUnityLoaded = false;
    }

    public native void initMod();
}