package it.filippocrocchini.spaceship.components;

import java.util.concurrent.ExecutionException;

import org.joml.Matrix4f;
import org.joml.Vector3f;
import org.joml.Vector3fc;

import it.filippocrocchini.engine.common.Color;
import it.filippocrocchini.engine.common.Engine;
import it.filippocrocchini.engine.common.GameObject;
import it.filippocrocchini.engine.common.component.Renderable;
import it.filippocrocchini.engine.common.graphics.model.Material;
import it.filippocrocchini.engine.common.graphics.model.Model;
import it.filippocrocchini.engine.common.graphics.model.Primitive;
import it.filippocrocchini.engine.common.physics.RigidBody;

public class ShipGraphics extends Renderable{
	private static Model shipModel;
	static {
		try {
			shipModel = (Model) Engine.loadResource(new Model("assets/ship.dae")).get();
		} catch (InterruptedException | ExecutionException e) {
			shipModel = null;
		}
	}

	private Matrix4f gizmoMatrix;
	private Matrix4f modelMatrix;
	private Vector3fc offset;
	
	public ShipGraphics(GameObject parent) {
		super(parent);
		this.offset = new Vector3f(0,-2.1f,-.7f);
		
		this.gizmoMatrix = new Matrix4f();
		this.modelMatrix = new Matrix4f();
		
		setMaterial(new Material("Phong"));
		material.setColor(new Vector3f(0,22/255f,6/255f));
	}

	@Override
	public boolean isAdvancedGl() {
		return true;
	}

	@Override
	public Model getModel() {
		return shipModel;
	}
	
	@Override
	protected void renderTransformInfo() {
		Engine.getDebugShader().bind();
		gizmoMatrix.set(modelMatrix).translate(offset);
		Engine.getDebugShader().setModelMatrixUniform(gizmoMatrix);
		
		Vector3f direction = parentGameObject.transform.getLocalX();
		Engine.getDebugShader().setModelColorUniform(Color.RED);
		Primitive.renderVector(direction.x,direction.y,direction.z,1);
		
		direction = parentGameObject.transform.getLocalY();
		Engine.getDebugShader().setModelColorUniform(Color.GREEN);
		Primitive.renderVector(direction.x,direction.y,direction.z,1);
		
		direction = parentGameObject.transform.getLocalZ();
		Engine.getDebugShader().setModelColorUniform(Color.BLUE);
		Primitive.renderVector(direction.x,direction.y,direction.z,1);
		
		RigidBody parentRigidBody = (RigidBody) parentGameObject.getComponentByName("RigidBody");
		if(parentRigidBody != null) {
			Engine.getDebugShader().setModelColorUniform(Color.YELLOW);
			direction = parentRigidBody.velocity;
			Primitive.renderVector(direction.x,direction.y,direction.z,1000);
		}
	}

	@Override
	public Matrix4f getModelMatrix() {
		return modelMatrix.identity().mul(getParentGameObject().transform.getModelViewMatrix()).translate(offset);
	}
}
