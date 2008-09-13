// ThroughputView.java

import edu.cmu.emulator.graph.*;
import java.awt.*;
import javax.swing.*;

public class ThroughputView {
	protected String	name;
	protected JFrame	frame;
	protected Graph2D	graph;
	protected Stroke	stroke;
	
	protected double	timeWidth = 60.0;
	protected double	minY = 0.0;
	protected double	maxY = 8.0;
	
	protected static final int	WIDTH = 600;
	protected static final int	HEIGHT = 600;
	
	protected static final int	BUF_SIZE = 600;

	protected Series[]	series;
	
		public ThroughputView(String name, Color[] seriesColors, Stroke stroke) {
		this.name = name;
		this.stroke = stroke;
		init(0, 0, seriesColors);
	}	
	
	public ThroughputView(String name, Color[] seriesColors) {
		this.name = name;
		init(0, 0, seriesColors);
	}

	
	public ThroughputView(String name, int x, int y, Color[] seriesColors) {
		this.name = name;
		init(x, y, seriesColors);
	}		
	
	public ThroughputView(String name, int x, int y, Color[] seriesColors, Stroke stroke) {
		this.stroke = stroke;
		this.name = name;
		init(x, y, seriesColors);
	}	
	
	public void setStroke(Stroke stroke) {
		this.stroke = stroke;
	}
	
	public void setPosition(int x, int y) {
		frame.setLocation(x, y);
	}

	public void addValues(double time, double[] vals) {
		if (vals.length != series.length) {
			throw new RuntimeException("not enough vals");
		}
		for (int i = 0; i < vals.length; i++) {
			series[i].addValue(time, vals[i]);
		}
		graph.setXWindow(time - timeWidth, time);
	}	
	
	protected void init(int x, int y, Color[] seriesColors) {
		double[] 	xVals;
		double[] 	yVals;
		
		xVals = new double[] {0};
		yVals = new double[] {minY};
		frame = new JFrame(name);
		frame.setSize(WIDTH + 30, HEIGHT + 40);
		graph = new Graph2D(WIDTH, HEIGHT, -timeWidth, 0.0, minY, maxY, 
							2.0, 10.0,
							0.2, 1.0, 
							false);
		graph.setXAxisLabel("Relative Time (seconds)");
		graph.setYAxisLabel("Throughput (MB)");
		series = new Series[seriesColors.length];
		for (int i = 0; i < seriesColors.length; i++) {
			series[i] = graph.addSeries(BUF_SIZE, xVals, yVals, seriesColors[i]);
			series[i].setStroke(stroke);
		}
		setPosition(x, y);
		frame.add(graph);
		frame.show();
	}
}
