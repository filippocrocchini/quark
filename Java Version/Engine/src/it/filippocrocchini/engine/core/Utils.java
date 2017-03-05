package it.filippocrocchini.engine.core;

import org.joml.Vector3f;

public final class Utils {
	public static Vector3f getRandomVector() {
		Vector3f vec = new Vector3f();
		
		vec.x = (float) Math.random();
		vec.y = (float) Math.random();
		vec.z = (float) Math.random();
		
		return vec;
	}
	
	public static float gaussianRandom() {
		float a = (float) Math.random();
		return (float) -Math.log(1-a);
	}
}
