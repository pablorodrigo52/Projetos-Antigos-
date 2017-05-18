import java.awt.BorderLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JButton;
import javax.swing.JFrame;
import static javax.swing.JFrame.EXIT_ON_CLOSE;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.table.DefaultTableModel;

/**
 *
 * @author Pablo Rodrigo
 */
public final class PrimeiraTela extends JFrame{
    
   private static String categoria = "efetivo"; //ponto de inicio..
   
   private JPanel painelCentralInferior, painelTabelaE, painelTabelaB, painelTabelaH, painelCentralSuperior;
   private JTable tabelaE, tabelaB, tabelaH;
   
   private JScrollPane barraRolagem;
   
   private final DefaultTableModel modelo = new DefaultTableModel();
   private final JTabbedPane tabbedPane = new JTabbedPane();

   
   public PrimeiraTela() throws ClassNotFoundException{
       super("CESAJU - BEM VINDO");
       criaJTable();
       criaPainelInferior();
       criaPainelSuperior();
   }
   
   
   public void criaPainelSuperior(){
       painelCentralSuperior = new JPanel();
       GridBagConstraints c = new GridBagConstraints();

       painelCentralSuperior.setLayout(new GridBagLayout());
       //painelCentralSuperior.setBackground(Color.YELLOW);
       c.fill = GridBagConstraints.HORIZONTAL;      
       
       
       c.gridx = 0; // X = COLUNA
       c.gridy = 0; // Y = LINHA
       c.insets = new Insets(1, 1, 1, 1); //distância de uma celula pra outra, 4 direções.
       c.weightx = 0.5;
       c.weighty = 0.5;       
       JLabel labelCESAJU = new JLabel("Associação CESAJU");
       painelCentralSuperior.add(labelCESAJU, c);
       
     
       c.gridx = 0; // X = COLUNA
       c.gridy = 3; // Y = LINHA
       c.insets = new Insets(1, 1, 1, 1); //distância de uma celula pra outra, 4 direções.
       c.weightx = 1.0;
       c.weighty = 1.0;       
       JLabel labelFinal = new JLabel("Membros atualmente cadastrados na associação: ");
       painelCentralSuperior.add(labelFinal, c);
       
       c.gridx = 5; // X = COLUNA
       c.gridy = 1; // Y = LINHA
       c.insets = new Insets(1, 1, 1, 1); //distância de uma celula pra outra, 4 direções.
       JButton buttonconsultas = new JButton("Consultas");
       buttonconsultas.addActionListener(new ActionListener() {
           @Override
           public void actionPerformed(ActionEvent e) {
               TelaConsultas tc = new TelaConsultas();
               tc.pack();
               tc.setVisible(true);
               tc.setResizable(false);
               tc.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
           }
       });
       painelCentralSuperior.add(buttonconsultas, c);
       
       c.gridx = 6; // X = COLUNA
       c.gridy = 1; // Y = LINHA
       c.insets = new Insets(1, 1, 1, 1); //distância de uma celula pra outra, 4 direções.     
       JButton buttonEx01 = new JButton("Novo Membro");
       buttonEx01.setEnabled(false); //false: desativa o botão novo membro
       painelCentralSuperior.add(buttonEx01, c);
       
       c.gridx = 5; // X = COLUNA
       c.gridy = 2; // Y = LINHA
       c.insets = new Insets(1, 1, 1, 1); //distância de uma celula pra outra, 4 direções.       
       JButton buttonEx02 = new JButton("Eventos");
       buttonEx02.setEnabled(false);
       painelCentralSuperior.add(buttonEx02, c);
       
       c.gridx = 6; // X = COLUNA
       c.gridy = 2; // Y = LINHA
       c.insets = new Insets(1, 1, 1, 1); //distância de uma celula pra outra, 4 direções.     
       JButton buttonEx03 = new JButton("Contribuições");
       buttonEx03.setEnabled(false);
       painelCentralSuperior.add(buttonEx03, c);
       
       getContentPane().add(painelCentralSuperior);
   }
   
   public void criaPainelInferior(){
       painelCentralInferior = new JPanel();
       painelCentralInferior.setLayout(new BorderLayout());  
        
       barraRolagem = new JScrollPane();
       
       painelTabelaE = new JPanel();
       painelTabelaE.setLayout(new BorderLayout());
       //painelTabelaE.setBackground(Color.BLUE);
       tabelaE.add(barraRolagem);
       painelTabelaE.add(BorderLayout.SOUTH, tabelaE);
   
       painelTabelaH = new JPanel();
       painelTabelaH.setLayout(new BorderLayout());
       //painelTabelaE.setBackground(Color.GREEN);
       tabelaH.add(barraRolagem);
       painelTabelaH.add(BorderLayout.SOUTH, tabelaH);
       
       painelTabelaB = new JPanel();
       painelTabelaB.setLayout(new BorderLayout());
       //painelTabelaE.setBackground(Color.YELLOW);
       tabelaB.add(barraRolagem);
       painelTabelaB.add(BorderLayout.SOUTH, tabelaB);
      
       
       tabbedPane.add("Efetivo", painelTabelaE);
       tabbedPane.add("Beneficiario", painelTabelaB);
       tabbedPane.add("Honorario", painelTabelaH);
      
       
       painelCentralInferior.add(BorderLayout.SOUTH, tabbedPane);
       
     
       tabbedPane.getModel().addChangeListener(new ChangeListener(){
           @Override
           public void stateChanged(ChangeEvent e){
               try {
                   novaAbaSelecionada();
                   //System.out.println("Mudei de Aba!!");
               } catch (ClassNotFoundException ex) {
                   Logger.getLogger(PrimeiraTela.class.getName()).log(Level.SEVERE, null, ex);
               }
           }
       });  
       
       getContentPane().add(painelCentralInferior, BorderLayout.SOUTH);
       setDefaultCloseOperation(EXIT_ON_CLOSE);
   }
   
   public void novaAbaSelecionada() throws ClassNotFoundException{
       ConexaoBD con = new ConexaoBD();
       
       switch (tabbedPane.getSelectedIndex()) {
           case 0:
               categoria = "efetivo";
               break;
           case 1:
               categoria = "beneficiario";
               break;
           case 2:
               categoria = "honorario";
               break;
           default:
               break;
       }
       pesquisar(modelo);
   }
   
   private void criaJTable() throws ClassNotFoundException {
		tabelaE = new JTable(modelo);
                tabelaH = new JTable(modelo);
                tabelaB = new JTable(modelo);
		modelo.addColumn("Cadastro");
		modelo.addColumn("Nome");
		modelo.addColumn("Email");
		modelo.addColumn("Condição");
                modelo.addColumn("CEP");
                modelo.addColumn("Endereço");
                
                //Configurações de tamaho para exibição..
                //tabelaE.setSize(800,230);
		tabelaE.getColumnModel().getColumn(0).setPreferredWidth(0); // cadastro
		tabelaE.getColumnModel().getColumn(3).setPreferredWidth(0); //condicao
                tabelaE.getColumnModel().getColumn(4).setPreferredWidth(0); //cep
               
                //tabelaB.setSize(800,230);
                tabelaB.getColumnModel().getColumn(0).setPreferredWidth(0); // cadastro
                tabelaB.getColumnModel().getColumn(3).setPreferredWidth(0); //condicao
                tabelaB.getColumnModel().getColumn(4).setPreferredWidth(0); //cep
                
                //tabelaH.setSize(800,230);
                tabelaH.getColumnModel().getColumn(0).setPreferredWidth(0); // cadastro
		tabelaH.getColumnModel().getColumn(3).setPreferredWidth(0); //condicao
                tabelaH.getColumnModel().getColumn(4).setPreferredWidth(0); //cep
                //Fim das configurações... são 3 tabelas diferentes por isso ficou grande.. tentei por tudo em uma só mas não deu
               
                pesquisar(modelo);
	}
   
   public static void pesquisar(DefaultTableModel modelo) throws ClassNotFoundException {
		modelo.setNumRows(0);
		ConexaoBD conexao = new ConexaoBD();

		for (Membro m : conexao.getInformacoesMembros(categoria)) {
			modelo.addRow(new Object[]{
                            m.getNum_Cadastro(),
                            m.getNome_Membro(),
                            m.getEmail_Membro(),
                            m.getCond_Membro(),
                            m.getCep_Membro(),
                            m.getRua_Membro() });
		}
	}

   public static void main(String[] args) throws ClassNotFoundException {
		PrimeiraTela ld = new PrimeiraTela();
		ld.show();
                ld.pack();
                ld.setResizable(true);
	}
}
// perguntar sobre as consultas.. se pode ser um numero x de consultas.. 