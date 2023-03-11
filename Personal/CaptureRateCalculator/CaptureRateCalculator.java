import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;
import javax.swing.border.Border;

public class CaptureRateCalculator {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		GridLayout layout = new GridLayout(0,1);
		JFrame frame = new JFrame();
		Color darkBG = new Color(31, 32, 30);
		Color lightText = new Color(220, 218, 217);
		Border border = BorderFactory.createLineBorder(Color.GRAY, 1);
		
		JLabel levelLabel = new JLabel("Pokemon's level:");
			levelLabel.setForeground(lightText);
		JTextField level = new JTextField("0");
			level.setBackground(darkBG);
			level.setForeground(lightText);
			level.setBorder(border);
			
		JLabel hpLabel = new JLabel("Remaining HP:");
		hpLabel.setForeground(lightText);
			JRadioButton full = new JRadioButton("> 75%", true);
			JRadioButton threeQ = new JRadioButton("<= 75%"); 
			JRadioButton half = new JRadioButton("<= 50%");
			JRadioButton oneQ = new JRadioButton("<= 25%"); 
			JRadioButton one = new JRadioButton("= 1");
		ButtonGroup hitPoints = new ButtonGroup();
			hitPoints.add(full);
			hitPoints.add(threeQ);
			hitPoints.add(half);
			hitPoints.add(oneQ);
			hitPoints.add(one);
			full.setBackground(darkBG);
			threeQ.setBackground(darkBG);
			half.setBackground(darkBG);
			oneQ.setBackground(darkBG);
			one.setBackground(darkBG);
			full.setForeground(lightText);
			threeQ.setForeground(lightText);
			half.setForeground(lightText);
			oneQ.setForeground(lightText);
			one.setForeground(lightText);
			
			
		JLabel evolLabel = new JLabel("Remaining Evolutions:");
		evolLabel.setForeground(lightText);
			JRadioButton evol1 = new JRadioButton("2");
			JRadioButton evol2 = new JRadioButton("1", true); 
			JRadioButton evol3 = new JRadioButton("None");

		ButtonGroup evolutions = new ButtonGroup();
			evolutions.add(evol1);
			evolutions.add(evol2);
			evolutions.add(evol3);
			evol1.setBackground(darkBG);
			evol2.setBackground(darkBG);
			evol3.setBackground(darkBG);
			evol1.setForeground(lightText);
			evol2.setForeground(lightText);
			evol3.setForeground(lightText);
			
		JLabel pAfflictionsLabel = new JLabel("Peristent Afflictions (Burned, Frozen, Paralysis, Poison) or Stuck");
			pAfflictionsLabel.setForeground(lightText);
		JSpinner persistentAff = new JSpinner();
			persistentAff.setValue(0);
			persistentAff.getEditor().getComponent(0).setBackground(darkBG);
			persistentAff.getEditor().getComponent(0).setForeground(lightText);
			persistentAff.setBorder(border);
		JLabel vAfflictionsLabel = new JLabel("Injuries, Volatile Afflictions (Sleep, Confused, Flinch, Infatuated...) or Slow");
			vAfflictionsLabel.setForeground(lightText);
		JSpinner volatileAff = new JSpinner();
			volatileAff.setValue(0);
			volatileAff.getEditor().getComponent(0).setBackground(darkBG);
			volatileAff.getEditor().getComponent(0).setForeground(lightText);
			volatileAff.setBorder(border);
			
		JLabel emptySpace = new JLabel("");
		JButton okButton = new JButton("Calculate");
			okButton.setBackground(Color.DARK_GRAY);
			okButton.setForeground(lightText);
		JLabel resultsLabel = new JLabel("Capture Rate = ");
			resultsLabel.setForeground(lightText);
		
		okButton.addActionListener(new ActionListener(){  
			public void actionPerformed(ActionEvent e){ 
				try {
					int captureRate = 100;
					int lv = Integer.parseInt(level.getText());
					captureRate -= lv * 2;
					//HP Markers
					if (full.isSelected()) { 
						captureRate -= 30;
					} else if (threeQ.isSelected()) {
						captureRate -= 15;
					} else if (oneQ.isSelected()) {
						captureRate += 15;
					} else if (one.isSelected()) {
						captureRate += 30;
					}
					//Evolutions
					if (evol1.isSelected()) {
						captureRate += 10;
					}else if (evol3.isSelected()) {
						captureRate -= 10;
					} 
					
					//Afflictions
					if ((int)persistentAff.getValue() > 0) {
						captureRate += (int)persistentAff.getValue() * 10;
					} 
					if ((int)volatileAff.getValue() > 0) {
						captureRate += (int)volatileAff.getValue() * 5;
					}
					
				    resultsLabel.setText("Capture Rate = " + captureRate); 
				} catch (NumberFormatException nfe) {
					resultsLabel.setText("Error! Level must be an Integer!");  
				}
				 
	        }  
	    }); 
		
		frame.add(levelLabel);
		frame.add(level);
		frame.add(hpLabel);
		frame.add(full);
		frame.add(threeQ);
		frame.add(half);
		frame.add(oneQ);
		frame.add(one);
		frame.add(evolLabel);
		frame.add(evol1);
		frame.add(evol2);
		frame.add(evol3);
		frame.add(pAfflictionsLabel);
		frame.add(persistentAff);
		frame.add(vAfflictionsLabel);
		frame.add(volatileAff);
		frame.add(emptySpace);
		frame.add(okButton);
		frame.add(resultsLabel);
		          
	
		
		
		frame.setSize(450,550);  
		frame.setLayout(layout);  
		frame.setVisible(true); 
		frame.getContentPane().setBackground(new Color(32, 31, 30));
		frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		}  
		
	}


