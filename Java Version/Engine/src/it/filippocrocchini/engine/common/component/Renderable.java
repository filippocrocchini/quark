package it.filippocrocchini.engine.common.component;

import org.joml.Matrix4f;
import org.joml.Vector3f;

import it.filippocrocchini.engine.common.Color;
import it.filippocrocchini.engine.common.Engine;
import it.filippocrocchini.engine.common.GameObject;
import it.filippocrocchini.engine.common.graphics.model.Material;
import it.filippocrocchini.engine.common.graphics.model.Model;
import it.filippocrocchini.engine.common.graphics.model.Primitive;
import it.filippocrocchini.engine.common.physics.RigidBody;

public abstract class Renderable extends Component{
	protected Material material;
	
	public Renderable(GameObject parent) {
		super(parent);
		material = new Material(null);
	}

	public void render() {}
	public boolean hasCustomRender() {return false;}
	
	public void renderDebugInfo() {
		renderTransformInfo();
	}

	public abstract boolean isAdvancedGl();
	public abstract Model getModel();
	public abstract Matrix4f getModelMatrix();
	
	public Material getMaterial() { return material; }
	public void setMaterial(Material material) {this.material = material;}
		
	protected void renderTransformInfo() {
		Engine.getDebugShader().bind();
		Engine.getDebugShader().setModelMatrixUniform(parentGameObject.transform.getPositionScaled());
		
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
}
