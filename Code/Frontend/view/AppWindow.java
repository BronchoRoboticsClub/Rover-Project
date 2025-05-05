package view;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.GridLayout;

import javax.swing.JFrame;
import controller.KeyPressListener;

public class AppWindow extends JFrame
{
    private InfoCanvas infoCanvas;

    public void init()
    {
        Container content = getContentPane();
        infoCanvas = new InfoCanvas();
        content.setLayout(new GridLayout(1, 1));
        content.add(infoCanvas, BorderLayout.CENTER);
        infoCanvas.requestFocusInWindow();
        infoCanvas.setFocusable(true);
        KeyPressListener keyPressListener = new KeyPressListener();
        infoCanvas.addKeyListener(keyPressListener);
    }

    public void updateCanvas()
    {
        infoCanvas.repaint();
    }

    public InfoCanvas getInfoCanvas()
    {
        return infoCanvas;
    }
}
