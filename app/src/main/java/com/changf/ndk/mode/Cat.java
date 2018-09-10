package com.changf.ndk.mode;

public class Cat extends Anima {

    public Cat(String name) {
        super(name);
    }

    public String getName() {
        return "new Cat().getName()-->My name is " + this.name;
    }
}
