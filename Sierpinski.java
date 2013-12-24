/* 
 Draws sierpinkski fractal
 author: Tom Hadlaw
*/

import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.event.*;
import java.awt.geom.Line2D;
import javax.swing.JFrame;
import javax.swing.JPanel;
import java.lang.Math;

public class Sierpinski extends JPanel
{
	
	public void drawSierpinski(Graphics2D g2, int x, int y, int size)
	{
		if (size <=2) return;
		Line2D b, l, r;

		b = new Line2D.Double(x, y, x + size, y);
		g2.draw(b);
		
		double h = Math.sqrt(size*size - (size/2)*(size/2));
		l = new Line2D.Double(x, y, x + size/2, y + h);
		g2.draw(l);

		r = new Line2D.Double(x + size/2, y + h, x + size, y);
		g2.draw(r);

		drawSierpinski(g2, x, y, size/2);
		drawSierpinski(g2, x + size/2, y, size/2);
		drawSierpinski(g2, x + size/4, y + ((int) h/2), size/2);
		
	}
	public void paint(Graphics g)
	{
		Graphics2D g2 = (Graphics2D) g;
		g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		drawSierpinski(g2, 100,100, 800);
	}

	public static void main(String[] args)
	{
		JFrame f = new JFrame();
		f.getContentPane().add(new Main());
		f.setSize(1000,1000);
		f.setVisible(true);
	}
}
