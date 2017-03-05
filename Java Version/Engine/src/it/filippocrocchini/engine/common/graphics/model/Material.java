package it.filippocrocchini.engine.common.graphics.model;

import static org.lwjgl.assimp.Assimp.AI_MATKEY_COLOR_AMBIENT;
import static org.lwjgl.assimp.Assimp.AI_MATKEY_COLOR_DIFFUSE;
import static org.lwjgl.assimp.Assimp.AI_MATKEY_COLOR_SPECULAR;
import static org.lwjgl.assimp.Assimp.aiGetErrorString;
import static org.lwjgl.assimp.Assimp.aiGetMaterialColor;
import static org.lwjgl.assimp.Assimp.aiTextureType_NONE;

import org.joml.Matrix4f;
import org.joml.Vector3f;
import org.lwjgl.assimp.AIColor4D;
import org.lwjgl.assimp.AIMaterial;

import it.filippocrocchini.engine.common.Engine;
import it.filippocrocchini.engine.common.graphics.shaders.ShaderProgram;

public class Material {
	private ShaderProgram shader = null;
	private String shaderName;
	private Vector3f color;
	
	private AIMaterial mMaterial;
	private AIColor4D mAmbientColor;
	private AIColor4D mDiffuseColor;
	private AIColor4D mSpecularColor;

	
	public Material(String shaderName) {
		this.shaderName = shaderName;
		color = new Vector3f();
	}

	public void useShader(Matrix4f projection, Matrix4f view, Matrix4f model) {
		if(getShader() != null) {
			getShader().bind();
			getShader().setProjectionMatrixUniform(projection);
			getShader().setViewMatrixUniform(view);
			getShader().setModelMatrixUniform(model);
			getShader().setModelColorUniform(color);
		}
	}
	
	public ShaderProgram getShader() {
		if(shaderName == null || !Engine.hasShader(shaderName)) return null;
		if(shader == null) {
			return Engine.getShader(shaderName);
		}
		return shader;
	}
	
	public void setColor(Vector3f color) {
		this.color = color;
	}

	@Deprecated
	public void set(AIMaterial material) {
		 mMaterial = material;
         String errorLog;
         
         mAmbientColor = AIColor4D.create();
         if (aiGetMaterialColor(mMaterial, AI_MATKEY_COLOR_AMBIENT, aiTextureType_NONE, 0, mAmbientColor) != 0) {
         	errorLog = aiGetErrorString();
         	System.err.println("Failed to load ambient color.");
             if(errorLog.length() > 0)
             	System.err.println(errorLog);
         }
         
         mDiffuseColor = AIColor4D.create();
         if (aiGetMaterialColor(mMaterial, AI_MATKEY_COLOR_DIFFUSE, aiTextureType_NONE, 0, mDiffuseColor) != 0) {
         	errorLog = aiGetErrorString();
         	System.err.println("Failed to load diffuse color.");
             if(errorLog.length() > 0)
             	System.err.println(errorLog);
         }
         
         mSpecularColor = AIColor4D.create();
         if (aiGetMaterialColor(mMaterial, AI_MATKEY_COLOR_SPECULAR, aiTextureType_NONE, 0, mSpecularColor) != 0) {
         	errorLog = aiGetErrorString();
         	System.err.println("Failed to load specular color.");
             if(errorLog.length() > 0)
             	System.err.println(errorLog);
         }
	}

}
