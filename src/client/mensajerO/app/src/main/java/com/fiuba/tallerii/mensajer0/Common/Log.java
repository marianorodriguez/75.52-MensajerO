package com.fiuba.tallerii.mensajer0.Common;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.io.File;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.logging.Logger;

public class Log {
    private DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
    private boolean doInfo, doDebug, doWarning, doError;
    private final String defaultPath = "log.txt";
    private static Logger instance = null;
    private PrintWriter writer;
    private String path;

    public static Logger getInstance() {
        if (instance == null) {
            instance = Logger.getLogger(Log.class.getName());
        }
        return instance;
    }

    public void info(String message) {
        if (doInfo) {
            write("INFO: " + message);
        }
    }

    public void debug(String message) {
        if (doDebug) {
            write("DEBUG: " + message);
        }
    }

    public void warning(String message) {
        if (doWarning) {
            write("WARNING: " + message);
        }
    }

    public void error(String message) {
        if (doError) {
            write("ERROR: " + message);
        }
    }

    private void write(String data) {
        Date date = new Date();
        writer.append(dateFormat.format(date) + " | " + data + "\n");
        writer.flush();
    }

    private Log() {
        path = "log.txt";
        doInfo = true;
        doDebug = true;
        doWarning = true;
        doError = true;

        try {
            writer = new PrintWriter(path, "UTF-8");
        } catch (FileNotFoundException | UnsupportedEncodingException e) {
            try {
                writer = new PrintWriter(defaultPath, "UTF-8");
                error("Couldn't find path " + path);
            } catch (FileNotFoundException | UnsupportedEncodingException e1) {
            }
        }
    }

}