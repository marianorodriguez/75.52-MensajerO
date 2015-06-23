package com.fiuba.tallerii.mensajer0.Common;

import android.content.Context;
import android.location.LocationListener;
import android.os.Bundle;
import android.widget.Toast;

/**
 * Created by fernando on 30/05/15.
 */
public class MyLocationListener implements LocationListener {

    Context context;

    public MyLocationListener(Context context) {
        this.context = context;
    }

    @Override
    public void onLocationChanged(android.location.Location loc) {
        loc.getLatitude();
        loc.getLongitude();
    }

    @Override
    public void onProviderDisabled(String provider) {

        Toast.makeText( context,
                "Gps Disabled",
                Toast.LENGTH_SHORT ).show();
    }

    @Override
    public void onProviderEnabled(String provider)
    {
        Toast.makeText( context,
                "Gps Enabled",
                Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onStatusChanged(String provider, int status, Bundle extras)
    {}

    public void setContext(Context context) {
        this.context = context;
    }

}

