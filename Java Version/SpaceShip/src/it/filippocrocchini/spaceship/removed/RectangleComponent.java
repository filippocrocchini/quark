import static org.lwjgl.opengl.GL11.GL_QUADS;
import static org.lwjgl.opengl.GL11.glBegin;
import static org.lwjgl.opengl.GL11.glEnd;
import static org.lwjgl.opengl.GL11.glVertex2d;

import it.filippocrocchini.engine.common.component.Renderable;
import it.filippocrocchini.engine.common.graphics.Model;
import it.filippocrocchini.engine.common.graphics.Transform;

public class RectangleComponent extends Renderable {
	public void render() {
		glBegin(GL_QUADS);
		glVertex2d(-.5, -.5);
		glVertex2d(-.5, .5);
		glVertex2d(.5, .5);
		glVertex2d(.5, -.5);
		glEnd();
	}

	@Override
	public Transform getTransform() {
		return null;
	}

	@Override
	public Model getModel() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public int getShader() {
		// TODO Auto-generated method stub
		return 0;
	}

}
