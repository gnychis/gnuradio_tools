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
    double[] throughput = new double[2];  // Two throughput values
    int currTime = 0;

    /////////// CREATE THROUGHPUT VIEW ///////////
    try {
      System.out.println("Starting graph...\n");

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
    
    /////////// CONTINUOUSLY READ VALUES ////////////
    while(true) {
      try {
        
        Thread.sleep(3000);  // Sleep while waiting for new values

        // Two processes, one to grab each new throughput value
        Process p1 = Runtime.getRuntime().exec("tail -n 1 /home/gnychis/client1");
        Process p2 = Runtime.getRuntime().exec("tail -n 1 /home/gnychis/client2");
        
        // Our input stream
        BufferedReader stdInput1 = new BufferedReader(new InputStreamReader(p1.getInputStream()));
        BufferedReader stdInput2 = new BufferedReader(new InputStreamReader(p2.getInputStream()));

        // Read the two throughput values from the input stream
        throughput[0] = Double.valueOf(stdInput1.readLine());
        throughput[1] = Double.valueOf(stdInput2.readLine());

        // Plot the values
        thrptView.addValues(currTime, throughput); 

        // Increment a logical time
        currTime++;
      }
      catch (Exception e) {
        e.printStackTrace();
        System.exit(-1);
      }
    }
		
	}

}
