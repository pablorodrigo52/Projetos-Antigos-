import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.WindowConstants;


public class AcoesBotao1 extends JFrame{
	// declaração do que é exibido na tela de interface
	JLabel labelNomeEmpresa = new JLabel ("  Informe o nome da empresa que você deseja cadastrar:");
	JLabel labelEndEmpresa = new JLabel ("  Informe o endereço da empresa que você deseja cadastrar:");
	JTextField nomeEmpresafield = new JTextField();		
	JTextField endEmpresafield = new JTextField();
	JButton botao1 = new JButton("Cancelar");
	JButton botao2 = new JButton("Continuar");
	
	public AcoesBotao1(){
		super ("Cadastrar empresa");  // barra de titulo
		
		final GridBagLayout gridbag = new GridBagLayout();
		GridBagConstraints cam = new GridBagConstraints();
		getContentPane().setLayout(gridbag);
		cam.gridwidth = GridBagConstraints.REMAINDER;
 
		gridbag.setConstraints(labelNomeEmpresa, cam);
		getContentPane().add(labelNomeEmpresa);
//-------------------------------------------------------------------------
		nomeEmpresafield.setPreferredSize(new Dimension(350,30));
		gridbag.setConstraints(nomeEmpresafield, cam);
		getContentPane().add(nomeEmpresafield);
//-------------------------------------------------------------------------		
		gridbag.setConstraints(labelEndEmpresa, cam);
		getContentPane().add(labelEndEmpresa);
//-------------------------------------------------------------------------
		endEmpresafield.setPreferredSize(new Dimension(350,30));
		gridbag.setConstraints(endEmpresafield, cam);
		getContentPane().add(endEmpresafield);
//-------------------------------------------------------------------------
		cam.gridwidth = GridBagConstraints.RELATIVE;
		botao1.setPreferredSize(new Dimension(90,30));
		gridbag.setConstraints(botao1, cam);
		getContentPane().add(botao1);
//-------------------------------------------------------------------------
		cam.gridwidth = GridBagConstraints.PAGE_END;
		botao2.setPreferredSize(new Dimension(90,30));
		gridbag.setConstraints(botao2, cam);
		getContentPane().add(botao2);
//-------------------------------------------------------------------------
		
		class botaoCancelar implements ActionListener{
			public void actionPerformed(ActionEvent e) {
				int confirm = JOptionPane.showConfirmDialog(null, "Você realmente deseja cancelar?","Cancelar",0);// pergunto se ele realmente deseja sair
				if (confirm == 0)  // não é 1,sim é 0
					System.exit(0);
			}
		}
		botao1.addActionListener(new botaoCancelar());  
		
		class botaoContinuar implements ActionListener{
			public void actionPerformed(ActionEvent e){ // Colocar pra escrever em arquivo..
				System.out.println(nomeEmpresafield.getText()+"\n");
				System.out.println(endEmpresafield.getText());				
				//JOptionPane.showConfirmDialog(null, "A empresa que você acabou de cadastrar está sem estoque atualmente, você deseja adicionar produtos ao estoque dela agora?", "Aviso",0);
			}
		}
		botao2.addActionListener(new botaoContinuar());
		
		
	}
}