package com.changf.ndk.mode;

public class Anima {
    protected String name;

    public Anima(String name) {
        this.name = name;
    }

    public String getName() {
        return "Called-->Animal.getName:"+name;
    }

}
