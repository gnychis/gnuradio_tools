// MACthroughput.java

//package emuExample;

import edu.cmu.emulator.*;
import edu.cmu.emulator.daemon.*;
import edu.cmu.emulator.world.*;
import edu.cmu.emulator.apps.iperf.*;
import java.io.*;
import java.util.ArrayList;

import edu.cmu.emulator.util.ColorParser;
import java.awt.*;
import java.io.IOException;
import java.util.*;


public class MACthroughput extends SimpleUserClass {
	protected ThroughputView	thrptView;
	protected double 			currentTimeSec;
	
	protected static final double	UPDATE_INTERVAL = 0.5;
	
	public void start(String[] args) {

    // Two colors, one for each graph
		Color[] 	colors;
		colors = new Color[2];
		colors[0] = ColorParser.parseColor("red");
		colors[1] = ColorParser.parseColor("blue");

    try {
      double[] throughput = new double[2];  // Two throughput values

      System.out.println("Starting graph...\n");

      // Create the ThroughputView
      try{
          BasicStroke     stroke;
          stroke = new BasicStroke((float)3.0);
          System.out.println("\n\t\t start throughput View: ");
          thrptView = new ThroughputView("MAC Throughput", 0,0, colors, stroke);
      } catch (Exception e) {
          e.printStackTrace();
      }

    } catch (Exception e) {
      e.printStackTrace();
    } finally {

    }
		
    System.out.println("Sweet\n");
	}

}
