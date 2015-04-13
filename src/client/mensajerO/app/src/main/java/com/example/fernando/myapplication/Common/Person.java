package com.example.fernando.myapplication.Common;

import android.support.annotation.NonNull;

import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;

/**
 * Created by fernando on 4/04/15.
 */
public class Person {

    public class Address {
        private String address;
        private String city;
        private String state;

        public String getAddress() {
            return address;
        }

        public void setAddress(String address) {
            this.address = address;
        }

        public String getCity() {
            return city;
        }

        public void setCity(String city) {
            this.city = city;
        }

        public String getState() {
            return state;
        }

        public void setState(String state) {
            this.state = state;
        }
    }

    public class PhoneNumber {
        private String type;
        private String number;

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }

        public String getNumber() {
            return number;
        }

        public void setNumber(String number) {
            this.number = number;
        }

    }

    private String name;
    private String surname;
    private Address address;
    private List<PhoneNumber> phoneList;
    private PhoneNumber num1;
    private PhoneNumber num2;

    public Person() {
        address = new Address();
        num1 = new PhoneNumber();
        num2 = new PhoneNumber();
    }

    public String getName() {
        return name;
    }

    public String getSurname() {
        return surname;
    }

    public Address getAddress() {
        return address;
    }

    public List<PhoneNumber> getPhoneList() {
        return phoneList;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public void setAddress(Address address) {
        this.address = address;
    }

    public void setPhoneList(List<PhoneNumber> phoneList) {
        this.phoneList = phoneList;
    }

    public PhoneNumber getNum1() {
        return num1;
    }

    public void setNum1(PhoneNumber num1) {
        this.num1 = num1;
    }

    public PhoneNumber getNum2() {
        return num2;
    }

    public void setNum2(PhoneNumber num2) {
        this.num2 = num2;
    }
}
