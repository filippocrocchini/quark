package it.filippocrocchini.engine.common.graphics;

import org.joml.Matrix4f;
import org.joml.Quaternionf;
import org.joml.Vector3f;
import org.joml.Vector3fc;

public class Transform {
	public Vector3f position;
	public Vector3f scale;

	private Matrix4f posMatrix;
	private Matrix4f posScaledMatrix;
	
	public Vector3f localRotationVec;
	public Vector3f worldRotationVec;
	
	public Quaternionf localRotation;
	public Quaternionf worldRotation;
	
	private Vector3f cameraPosition;
	private Matrix4f cameraViewMatrix;
	private Quaternionf localCameraRotation;
	private Quaternionf worldCameraRotation;
	
	private Matrix4f modelMatrix;
	
	public static final Vector3fc globalX = new Vector3f(1,0,0).toImmutable();
	public static final Vector3fc globalY = new Vector3f(0,1,0).toImmutable();
	public static final Vector3fc globalZ = new Vector3f(0,0,1).toImmutable();
	
	public Vector3f localX = new Vector3f(1,0,0);
	public Vector3f localY = new Vector3f(0,1,0);
	public Vector3f localZ = new Vector3f(0,0,1);

	public Transform() {
		position = new Vector3f();
		cameraPosition = new Vector3f();
		scale = new Vector3f(1,1,1);
		
		worldRotation = new Quaternionf().lookAlong(new Vector3f(0,0,1), new Vector3f(0,1,0));
		localRotation = new Quaternionf().lookAlong(new Vector3f(0,0,1), new Vector3f(0,1,0));

		localCameraRotation = new Quaternionf().lookAlong(new Vector3f(0,0,1), new Vector3f(0,1,0));
		worldCameraRotation = new Quaternionf().lookAlong(new Vector3f(0,0,1), new Vector3f(0,1,0));
		
		posMatrix = new Matrix4f().identity();
		cameraViewMatrix = new Matrix4f().identity();
		modelMatrix = new Matrix4f().identity();
		posScaledMatrix = new Matrix4f().identity();
		
	}
	
	public Matrix4f getPosMatrix() {
		return posMatrix.identity().translate(position);
	}

	public Matrix4f getModelViewMatrix() {
		modelMatrix.identity().rotate(worldRotation).translate(position).rotate(localRotation).scale(scale);
		return modelMatrix;
	}
	
	public Matrix4f getCameraViewMatrix() {
		
		cameraViewMatrix.identity();
		
		worldCameraRotation.set(worldRotation).invert();
		localCameraRotation.set(localRotation).invert();
		cameraPosition.set(position).mul(-1);
		
		cameraViewMatrix.rotate(localCameraRotation).translate(cameraPosition).rotate(worldCameraRotation); 
		
		return cameraViewMatrix;
	}
	
	public void rotateLocal(Vector3f deltaRot) {
		rotateLocal(deltaRot.x, deltaRot.y, deltaRot.z);
	}
	
	private Quaternionf deltaRotation = new Quaternionf();
	
	public void rotateLocal(float pitch, float yaw, float roll) {
		deltaRotation.set(pitch, yaw, roll);
		localRotation.mul(deltaRotation);
		
		localX.set(1,0,0);
		localY.set(0,1,0);
		localZ.set(0,0,1);
		
		localRotation.transform(localX);
		localRotation.transform(localY);
		localRotation.transform(localZ);
	}
	
	public Vector3f getLocalX() {
		return localX;
	}

	public Vector3f getLocalY() {
		return localY;
	}

	public Vector3f getLocalZ() {
		return localZ;
	}

	public Matrix4f getPositionScaled() {
		posScaledMatrix.identity().translate(position).scale(scale);
		return posScaledMatrix;
	}

}
