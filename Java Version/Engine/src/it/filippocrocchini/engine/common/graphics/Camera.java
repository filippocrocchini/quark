package it.filippocrocchini.engine.common.graphics;

import org.joml.Matrix4f;

import it.filippocrocchini.engine.common.GameObject;
import it.filippocrocchini.engine.common.component.Component;

public class Camera extends Component{
	private Matrix4f projectionMatrix;
	private Matrix4f viewProjectionMatrix;
	
	public Camera(GameObject parent, float left, float right, float bottom, float top, float zNear, float zFar) {
		super(parent);
		createMatrices();
		projectionMatrix.setOrtho(left, right, bottom, top, zNear, zFar);
	}
	
	public Camera(GameObject parent, float fovy, float aspect, float zNear, float zFar) {
		super(parent);
		createMatrices();
		projectionMatrix.perspective((float) Math.toRadians(fovy), aspect, zNear, zFar);
	}
	
	private void createMatrices() {
		projectionMatrix = new Matrix4f().identity();
		viewProjectionMatrix = new Matrix4f().identity();
	}
	
	public Matrix4f getViewMatrix() {
		return parentGameObject.transform.getCameraViewMatrix();
	}
	
	public Matrix4f getProjectionMatrix() {
		return projectionMatrix;
	}

	public Matrix4f getViewProjectionMatrix() {
		return viewProjectionMatrix.identity().mul(getViewMatrix()).mul(getProjectionMatrix());
	}
}
