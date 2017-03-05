package it.filippocrocchini.engine.removed;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.IntBuffer;
import java.util.Scanner;

import org.lwjgl.BufferUtils;
import org.lwjgl.PointerBuffer;

import static org.lwjgl.opengl.GL15.*;
import static org.lwjgl.opengl.GL20.*;

import it.filippocrocchini.engine.common.resource.Resource;
import it.filippocrocchini.engine.core.Utils;

@Deprecated
public class ShaderResource implements Resource {
	private int type;
	private String pathToFile;
	
	public int shaderIndex;
	
	public ShaderResource(int type, String pathToFile) {
		this.type = type;
		this.pathToFile = pathToFile;
	}
	
	public ShaderResource(String source, int type) {
		this.type = type;
		this.pathToFile = pathToFile;
	}

	@Override
	public void onRawLoad() throws IOException {
	}

	@Override
	public void onGlLoad(){	
		shaderIndex = loadShader(new File(pathToFile), type);
	}
	
	 public static int loadShader(File file, int type) {
	        try {
	            Scanner sc = new Scanner(file);
	            StringBuilder data = new StringBuilder();
	             
	            if(file.exists()) {
	                while(sc.hasNextLine()) {
	                    data.append(sc.nextLine() + "\n");
	                }
	                 
	                sc.close();
	            }
	            int id = glCreateShader(type);
	            glShaderSource(id, data);
	            glCompileShader(id);
	            return id;
	        }
	         
	        catch (FileNotFoundException e) {
	            e.printStackTrace();
	        }
	        return -1;
	    }

	@Override
	public void glCleanup() {
	}
}
