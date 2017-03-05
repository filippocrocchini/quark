package it.filippocrocchini.spaceship.components.controllers;

import java.nio.DoubleBuffer;

import org.joml.Vector3f;
import org.lwjgl.BufferUtils;
import org.lwjgl.glfw.GLFW;

import it.filippocrocchini.engine.common.Engine;
import it.filippocrocchini.engine.common.GameObject;
import it.filippocrocchini.engine.common.component.Updatable;
import it.filippocrocchini.engine.common.physics.RigidBody;

public class PlayerController extends Updatable{
	
	private DoubleBuffer oldx = BufferUtils.createDoubleBuffer(1);
	private DoubleBuffer oldy = BufferUtils.createDoubleBuffer(1);
	private DoubleBuffer mousex = BufferUtils.createDoubleBuffer(1);
	private DoubleBuffer mousey = BufferUtils.createDoubleBuffer(1);

	private boolean wasCaptured;
	
	private double mouseSensbility = 0.0002;
	
	private Vector3f direction;
	
	public PlayerController(GameObject parent) {
		super(parent);
		direction = new Vector3f();
	}
	@Override
	public void update(double delta) {
		if(Engine.isMouseCaptured()) {			
			direction.set(0);
			
			if(GLFW.glfwGetKey(Engine.getWindow(), GLFW.GLFW_KEY_W) == GLFW.GLFW_PRESS) {
				direction.add(getParentGameObject().transform.getLocalZ()).mul(-1);
			}
			if(GLFW.glfwGetKey(Engine.getWindow(), GLFW.GLFW_KEY_A) == GLFW.GLFW_PRESS) {
				direction.add(getParentGameObject().transform.getLocalX()).mul(-1);
			}
			if(GLFW.glfwGetKey(Engine.getWindow(), GLFW.GLFW_KEY_S) == GLFW.GLFW_PRESS) {
				direction.add(getParentGameObject().transform.getLocalZ());
			}
			if(GLFW.glfwGetKey(Engine.getWindow(), GLFW.GLFW_KEY_D) == GLFW.GLFW_PRESS) {
				direction.add(getParentGameObject().transform.getLocalX());
			}
			
			RigidBody parentRigidBody = (RigidBody) parentGameObject.getComponentByName("RigidBody");
			if(parentRigidBody != null) {
				parentRigidBody.applyImpulse(direction.mul(0.01f), null, delta);
			}
			
			
			oldx.clear();
			oldx.put(mousex.get(0));
			oldy.clear();
			oldy.put(mousey.get(0));
			
			GLFW.glfwGetCursorPos(Engine.getWindow(), mousex, mousey);
			
			if(!wasCaptured) {
				oldx.clear();
				oldx.put(mousex.get(0));
				oldy.clear();
				oldy.put(mousey.get(0));
			}
			
			float deltayAngle = (float)((mousex.get(0) - oldx.get(0)) * delta * mouseSensbility);
			float deltaxAngle = (float)((mousey.get(0) - oldy.get(0)) * delta * mouseSensbility);
			
			getParentGameObject().transform.rotateLocal(-deltaxAngle, -deltayAngle, 0);
		}
		
		wasCaptured = Engine.isMouseCaptured();
	}

}
