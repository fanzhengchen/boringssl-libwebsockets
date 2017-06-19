package com.example;

public class WebSocket {

    public WebSocket() {
        SoLoader.loadLib("websocket");
    }

    public native void setAddress(String address, int port, String path);

    public native void setUrl(String url);

    public native void connect();
}
