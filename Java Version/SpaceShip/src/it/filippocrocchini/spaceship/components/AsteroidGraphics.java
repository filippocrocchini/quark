package it.filippocrocchini.spaceship.components;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutionException;

import org.joml.Matrix4f;
import org.joml.Vector3f;

import it.filippocrocchini.engine.common.Engine;
import it.filippocrocchini.engine.common.GameObject;
import it.filippocrocchini.engine.common.component.Renderable;
import it.filippocrocchini.engine.common.graphics.model.Material;
import it.filippocrocchini.engine.common.graphics.model.Model;

public class AsteroidGraphics extends Renderable{
	private static List<Model> asteroidModels = new ArrayList<>();
	static {
		for(int i=0; i<1; i++) {
			try {
				asteroidModels.add((Model) Engine.loadResource(new Model("assets/asteroids/"+i+".obj")).get());
			} catch (InterruptedException | ExecutionException e) {
			}
		}
	}
	public final int modelIndex = (int)(Math.random() * asteroidModels.size());
	
	public AsteroidGraphics(GameObject parent) {
		super(parent);
		
		setMaterial(new Material("Phong"));
		material.setColor(new Vector3f(0.1f,0.05f,0.05f));
	}

	@Override
	public Model getModel() {
		return asteroidModels.get(modelIndex);
	}

	@Override
	public Matrix4f getModelMatrix() {
		return getParentGameObject().transform.getModelViewMatrix();
	}

	@Override
	public boolean isAdvancedGl() {
		return true;
	}

}
