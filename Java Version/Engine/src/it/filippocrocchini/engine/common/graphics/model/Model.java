package it.filippocrocchini.engine.common.graphics.model;

import static org.lwjgl.assimp.Assimp.aiImportFile;
import static org.lwjgl.assimp.Assimp.aiProcess_JoinIdenticalVertices;
import static org.lwjgl.assimp.Assimp.aiProcess_Triangulate;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.opengl.GL11.GL_UNSIGNED_INT;
import static org.lwjgl.opengl.GL11.glDrawElements;
import static org.lwjgl.opengl.GL30.glBindVertexArray;

import java.io.IOException;

import org.joml.Matrix4f;
import org.lwjgl.PointerBuffer;
import org.lwjgl.assimp.AIMesh;
import org.lwjgl.assimp.AIScene;

import it.filippocrocchini.engine.common.Engine;
import it.filippocrocchini.engine.common.resource.Resource;

public class Model implements Resource{
	private AIScene scene;
	private Mesh[] meshes;
	private String pathToFile;
	
	public Model(String path) {
		this.pathToFile = path;
	}
	
	public void render(Material material, Matrix4f projection, Matrix4f view, Matrix4f model) {
		material.useShader(projection, view, model);
		for(Mesh mesh : meshes) {
			glBindVertexArray(mesh.getVao());
			glDrawElements(Engine.isShowingDebugInfo()?GL_LINES:GL_TRIANGLES, mesh.getElementCount(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}

	@Override
	public void onRawLoad() throws AssertionError, IOException {
		scene = aiImportFile(pathToFile, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate);
        int meshCount = scene.mNumMeshes();
        
        meshes = new Mesh[meshCount];
        PointerBuffer meshesBuffer = scene.mMeshes();
        for (int i = 0; i < meshCount; ++i) {
            meshes[i] = new Mesh(AIMesh.create(meshesBuffer.get(i)));
        }

// NOTE: Not using materials imported by assimp, i mean.. who cares right? ;P
        
//        int materialCount = scene.mNumMaterials();
//        PointerBuffer materialsBuffer = scene.mMaterials();
//        if(materialCount > 1)
//        	System.err.println("Only one material will be used!!");
//        material.set(AIMaterial.create(materialsBuffer.get(0)));
    }

	@Override
	public void onGlLoad() throws AssertionError {
		for(Mesh mesh : meshes) {
    		mesh.load();
    	}
	}

	@Override
	public void glCleanup() {
		for(Mesh mesh : meshes) {
	    	mesh.cleanup();
    	}
	}
}
