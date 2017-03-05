package it.filippocrocchini.engine.common.component;

import it.filippocrocchini.engine.common.GameObject;

public abstract class Updatable extends Component{	
	public Updatable(GameObject parent) {
		super(parent);
	}

	public abstract void update(double delta);
}
