import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;


public class AcoesBotao3 extends JFrame{
	
	JLabel label1 = new JLabel ("                                  Bem vindo ao menu do estoque, o que você deseja fazer ?");
	JButton botao1 = new JButton ("Verificar se uma empresa está cadastrada");
	JButton botao2 = new JButton("Ver os produtos que uma empresa possui");
	JButton botao3 = new JButton("Adicionar produtos em uma empresa já cadastrada");
//	JButton botao4 = new JButton("Sair");
	
	public AcoesBotao3(){
		super("Estoque");
		
		Container containerBorder = getContentPane();  // aqui eu crio o container da tela.. onde será mostrado todo o conteudo da janela para o usuario..
		containerBorder.setLayout( new BorderLayout() ); // defino qual será o layout do container.. tenho que verificar qual o melhor..
		
		containerBorder.add(BorderLayout.NORTH,label1);// e adiciono o label ao container.. queria adicionar ele superior mas no centro.. 
		
		final Container containerGrid = getContentPane();
		containerGrid.setLayout( new GridLayout(4,0,10,0) );  // Li, Co, H, V
		
		botao1.setBorderPainted(false);
		botao2.setBorderPainted(false);
		botao3.setBorderPainted(false);
//		botao4.setBorderPainted(false);
		
		containerGrid.add(botao1);  // adiciono os botoes ao container.. 
		containerGrid.add(botao2);
		containerGrid.add(botao3);
//		containerGrid.add(botao4);
	
                botao1.setEnabled(false);
                botao2.setEnabled(false);
                botao3.setEnabled(false);
//		class Botao4 implements ActionListener{ 
//			public void actionPerformed(ActionEvent e) {
//				int confirm = JOptionPane.showConfirmDialog(containerGrid, "Você realmente deseja sair?", "Sair", 0);// pergunto se ele realmente deseja sair
//					if (confirm == 0)  // não é 1,sim é 0
//						setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);				
//			} // fim do actionPerfomed
//		}// fim do action Listener
//		botao4.addActionListener(new Botao4 ());  // o botão 4 fará essa ação acima, encerra a classe empresário. 
//---------------------------------------------------------------------------------------------------------------------------
		
	}
	
}
