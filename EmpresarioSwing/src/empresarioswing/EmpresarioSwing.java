import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.WindowConstants;

public class EmpresarioSwing extends JFrame{
 
	private JLabel label1;
	private JButton botao1, botao2, botao3, botao4;
	
	public EmpresarioSwing(){ // Método construtor da classe EmpresarioSwing
		super("Empresário"); // esse super representa o titulo da janela, poderei mudar se quiser.. 
		
		Container containerBorder = getContentPane();  // aqui eu crio o container da tela.. onde será mostrado todo o conteudo da janela para o usuario..
		containerBorder.setLayout( new BorderLayout() ); // defino qual será o layout do container.. tenho que verificar qual o melhor..
		label1 = new JLabel("                                  Bem Vindo ao menu Empresário. O que você deseja fazer ?");// Defino o que terá escrito no label.. 
		containerBorder.add(BorderLayout.NORTH,label1);// e adiciono o label ao container.. queria adicionar ele superior mas no centro.. 
		
		final Container containerGrid = getContentPane();
		containerGrid.setLayout( new GridLayout(5,0,10,0) );  // Li, Co, H, V
		
		botao1 = new JButton("Cadastrar uma Empresa");
		botao2 = new JButton("Verificar Empresas Cadastradas");
		botao3 = new JButton("Estoque");
		botao4 = new JButton("Sair");		
		
		botao1.setBorderPainted(false);
		botao2.setBorderPainted(false);
		botao3.setBorderPainted(false);
		botao4.setBorderPainted(false);
		
		containerGrid.add(botao1);  // adiciono os botoes ao container.. 
		containerGrid.add(botao2);
		containerGrid.add(botao3);
		containerGrid.add(botao4);
		
		class Botao4 implements ActionListener{ 
			public void actionPerformed(ActionEvent e) {
				int confirm = JOptionPane.showConfirmDialog(containerGrid, "Você realmente deseja sair?", "Sair", 0);// pergunto se ele realmente deseja sair
					if (confirm == 0)  // não é 1,sim é 0
						System.exit(0);				
			} // fim do actionPerfomed
		}// fim do action Listener
		botao4.addActionListener(new Botao4 ());  // o botão 4 fará essa ação acima, encerra a classe empresário. 
//-------------------------------------------------------------------------------------------------------------------------
	    class Botao1 implements ActionListener{
			public void actionPerformed(ActionEvent e) {
				AcoesBotao1 ac = new AcoesBotao1 ();
				ac.setSize(400,200);            // aqui são algumas caracteristicas da janela que o botao1 abre
				ac.setResizable(false);         // ........
				ac.setVisible(true);            // ...........
				ac.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
			}
	    }
		botao1.addActionListener(new Botao1 ()); // o botão 1 fará essa ação acima, tive que criar uma clase 
												//para o botão 1, e dizer quais são suas ações.. 
//-------------------------------------------------------------------------------------------------------------------------
		class Botao2 implements ActionListener{
			public void actionPerformed (ActionEvent e){
				AcoesBotao2 ac2 = new AcoesBotao2 ();
				ac2.setSize(500,300);
				ac2.setResizable(true);
				ac2.setVisible(true);
				ac2.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
			}
		}
	    botao2.addActionListener(new Botao2());
//-------------------------------------------------------------------------------------------------------------------------
	   class Botao3 implements ActionListener{
		   public void actionPerformed (ActionEvent e){
			   AcoesBotao3 ac3 = new AcoesBotao3();
			   ac3.setSize(540,220);
			   ac3.setResizable(false);
			   ac3.setVisible(true);
			   ac3.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
		   }
	   }
	   botao3.addActionListener(new Botao3());
	
	}
}