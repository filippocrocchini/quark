package it.filippocrocchini.engine.common;

public class Color {
	public static final Color RED = new Color(1,0,0);
	public static final Color GREEN = new Color(0,1,0);
	public static final Color BLUE = new Color(0,0,1);
	public static final Color YELLOW = new Color(1,1,0);
	
	public float r;
	public float g;
	public float b;
	
	public Color(float r, float g, float b) {
		this.r = r;
		this.g = g;
		this.b = b;
	}
}
