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
	protected RemoteProcess		serverProcess;
	protected EmuNode[]			nodes;
	protected ThroughputView	thrptView;
	protected double 			currentTimeSec;
	
	protected static final double	UPDATE_INTERVAL = 0.5;
	
	protected int doRemoteExecAndWait(String nodeName, String cmd, String outputBase) {		
		int	result;
		
//		System.out.println("about to call execProcess: "+ cmd);
		result = dComm.execProcessAndWait_CentralLogIO(nodeName, 
						cmd, // the process to run
						outputBase +"."+ nodeName +".stdout", // name of stdout file
						outputBase +"."+ nodeName +".stderr"
						); // name of stderr file
						// output will be stored in the directory where the emulator was started when using Central IO
//		System.out.println("execProcess has returned");
		return result;
	}
	
	protected RemoteProcess doRemoteExec(String nodeName, String cmd, String outputBase) {
		RemoteProcess	rProc;
		
//		System.out.println("about to call execProcess: "+ cmd);
		rProc = dComm.execProcess_CentralLogIO(nodeName, 
						cmd, // the process to run
						outputBase +"."+ nodeName +".stdout", // name of stdout file
						outputBase +"."+ nodeName +".stderr"); // name of stderr file
						// output will be stored in the directory where the emulator was started when using Central IO
//		System.out.println("execProcess has returned");
		return rProc;
	}
	
	
	protected void cleanNode(String nodeName) {
		System.out.println("cleaning: "+ nodeName);
		doRemoteExecAndWait(nodeName, "killall -9 -v iperf", "clean");
	}
	
	public RemoteProcess runServer(String nodeName) {
		return doRemoteExec(nodeName, "iperf -s", "server");
	}

	public int runClient(EmuNode clientNode, EmuNode serverNode, int count) {
		String	serverIP;
		
		serverIP = serverNode.getNIC(0).getIPString();
		System.out.println("serverIP: "+ serverIP);
		return doRemoteExecAndWait( clientNode.getUName(), 
					"iperf -t 5 -i 0.5 -c "+ serverIP, 
					"client-"+ clientNode.getUName() +"-"+ serverNode.getUName() + "." + count);
	}	
	
	public double doTest(EmuNode clientNode, EmuNode serverNode, int batchs) {
		String		resultFile;
		IPerfResult	result;
		double[]		throughput;
		int		count;
		
		throughput = new double[1];
		count = batchs * 30/5;
		currentTimeSec = EmuSynch.curTimeSecs();
		try {
			System.out.println();
			System.out.println("Running test: "
				+ clientNode.getUName() +"->"+ serverNode.getUName());
			System.out.println("cleaning server...");
			cleanNode( serverNode.getUName() );
			System.out.println("cleaning client...");
			cleanNode( clientNode.getUName() );
			System.out.println("starting server...");
			serverProcess = runServer( serverNode.getUName() );
			try {
				Thread.sleep(2* 1000);
			} catch (InterruptedException ie) {
			}
			System.out.println("running client...");
			for (int runCount = 0; runCount < count; runCount ++){  
				runClient(clientNode, serverNode, runCount);
				resultFile = "client-"+clientNode.getUName() +"-"
						+ serverNode.getUName() + "." + runCount +"."+ clientNode.getUName() +".stdout";
				try {
					Thread.sleep(1000);
				} catch (InterruptedException ie) {
				}
			
				try {
					ArrayList<IPerfResult>	results;
				
					results = IPerfParser.parse( new FileInputStream(resultFile)); 
					if (results.size() > 0) {
						for(int i = 0;i < results.size();i ++){
							result = results.get(i);
							throughput[0] = result.getMbps();
//							System.out.println("Result: ( " + i + " ) "+ throughput[0]);
							currentTimeSec = currentTimeSec + UPDATE_INTERVAL;
							thrptView.addValues(currentTimeSec, throughput);
						}
						result = results.get(0);
						throughput[0] = result.getMbps();
					} else {
//						System.out.println("NO RESULT");
						throughput[0] = 0.0;
						for(int i = 0;i < 10;i++){
							currentTimeSec = currentTimeSec + UPDATE_INTERVAL;
							thrptView.addValues(currentTimeSec, throughput);
						}
					}
				} catch (IOException ioe) {
					ioe.printStackTrace();
					throughput[0] = Double.NaN;
				}
			}
			System.out.println("client is complete");
			System.out.println("stopping server");
			serverProcess.destroy();
			try {
				Thread.sleep(2*1000);
			} catch (InterruptedException ie) {
			}
		} catch (RuntimeException re) {
			throw re;
		} 
		throughput[0] = Double.NaN;
		return throughput[0];
	}
	
	public void start(String[] args) {
		Color[] 	colors;
		colors = new Color[1];
		colors[0] = ColorParser.parseColor("red");
		
		try {
			double	throughput;
			int timeSlots;
			System.out.println("Throughput test (IPerf) start.");
			if (args.length != 3) {
				System.out.println("args: <node1> <node2> <# of time slot>");
				System.out.println("must specify 2 nodes, one time slot = 30 seconds");
				System.out.println("e.g. nodew1 nodew2 3");
				return;
			}
			
			timeSlots = Integer.parseInt(args[args.length-1]);
			// sanity check arguments
			if (args.length - 1 > numNodes) {
				throw new RuntimeException("too many nodes");
			}
			
			if ( args[0].equals(args[1]) ) {
				throw new RuntimeException("duplicate nodes: "
									+ args[0] +" "+ args[1]);
			}
			
			nodes = new EmuNode[args.length-1 ];
			for (int i = 0; i < nodes.length; i++) {
				nodes[i] = world.getNode(args[i ]);
				if (nodes[i] == null) {
					throw new RuntimeException("no such node: "+ args[i ]);
				}
			}

            try{
                BasicStroke     stroke;

                stroke = new BasicStroke((float)3.0);
                System.out.println("\n\t\t start throughput View: ");
                thrptView = new ThroughputView("Throughput", 0,0, colors, stroke);
            } catch (Exception e) {
                e.printStackTrace();
            }



			System.out.println("\n\nRunning iperf test for: ");
			for (int i = 0; i < nodes.length; i++) {
				System.out.println("\t"+ nodes[i].getUName() );
			}
			System.out.println();
			
			throughput = doTest(nodes[0], nodes[1],timeSlots);
			
			System.out.println("Complete.");
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			//stopDevs();
		}
	}

}
