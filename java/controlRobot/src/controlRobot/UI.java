package controlRobot;

import org.eclipse.swt.widgets.Composite;

public class UI extends Composite {

	/**
	 * Create the composite.
	 * @param parent
	 * @param style
	 */
	public UI(Composite parent, int style) {
		super(parent, style);

	}

	@Override
	protected void checkSubclass() {
		// Disable the check that prevents subclassing of SWT components
	}

}
