package com.example;

/**
 * Created by mark on 17-6-19.
 */

public class SoLoader {

    public static void loadLib(String libname) {
        try {
            System.loadLibrary(libname);
        } catch (UnsatisfiedLinkError error) {
            System.out.printf("%s unsatified link erro", libname);
            error.printStackTrace();
        }
    }
}
