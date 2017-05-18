
import java.awt.BorderLayout;
import java.awt.Dimension;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Pablo Rodrigo
 */
public class ActionsBotoesConsultas extends JFrame {
   
    private final DefaultTableModel modelo = new DefaultTableModel();
    private JScrollPane scrollpane;
    ConexaoBD conexao = new ConexaoBD();
    
   public ActionsBotoesConsultas(){
       super("Resultado da Consulta");
   }
    
    public void CriaTabela1 () throws ClassNotFoundException{
        JFrame frame = new JFrame();
        JLabel consulta = new JLabel("-- Informe os tipos de eventos existentes:");
        JTable tabelaBotao1 = new JTable (modelo);
        tabelaBotao1.setEnabled(false);
        scrollpane = new JScrollPane(tabelaBotao1);
        scrollpane.setPreferredSize(new Dimension(70,200));
        modelo.setNumRows(0);
        modelo.addColumn("Nome");
        modelo.addColumn("Descrição");
        tabelaBotao1.getColumnModel().getColumn(0).setPreferredWidth(0); // tamanho da coluna.. 
        tabelaBotao1.getColumnModel().getColumn(1).setPreferredWidth(600);
        frame.setLayout(new BorderLayout());
        frame.add(BorderLayout.CENTER, consulta); //Adiciono a pergunta no frame..
       
        for (TipoEvento te : conexao.getInformacoesTipoEvento()) {
			modelo.addRow(new Object[]{
                            te.getNome_TipoEvento(),
                            te.getDescri_TipoEvento()
                            });
		}
        frame.add(BorderLayout.SOUTH, scrollpane);
        frame.setVisible(true);
        frame.setSize(800,300);
        frame.setResizable(false);
        frame.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        
    }
    
    
    public void CriaTabela2() throws ClassNotFoundException{
        JFrame frame = new JFrame();
        JLabel consulta = new JLabel("-- Informe o nome e a hora dos eventos que acontecerão no local da associação CESAJU:");
        JTable tabelaBotao1 = new JTable (modelo);
        tabelaBotao1.setEnabled(false);
        scrollpane = new JScrollPane(tabelaBotao1);
        scrollpane.setPreferredSize(new Dimension(40,200));
        modelo.setNumRows(0);
        modelo.addColumn("Nome");
        modelo.addColumn("Local");
        modelo.addColumn("Hora");
        
        frame.setLayout(new BorderLayout());
        frame.add(BorderLayout.CENTER, consulta); //Adiciono a pergunta no frame..
        for (EventoLocalCesaju elc : conexao.getInformacoesEventoCesaju()) {
			modelo.addRow(new Object[]{
                            elc.getNome_Evento(),
                            elc.getLocal_Evento(),
                            elc.getData_Evento()
                            });
        }
        frame.add(BorderLayout.SOUTH, scrollpane);
        frame.setVisible(true);
        frame.setSize(800,300);
        frame.setResizable(false);
        frame.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
    }
    
   
    public void CriaTabela3() throws ClassNotFoundException{
        JFrame frame = new JFrame();
        JLabel consulta = new JLabel("-- Selecione todos os membros que ja pagaram mensalidade para a associação alguma vez, sem repetição de nomes:");
        JTable tabelaBotao1 = new JTable (modelo);
        tabelaBotao1.setEnabled(false);
        scrollpane = new JScrollPane(tabelaBotao1);
        scrollpane.setPreferredSize(new Dimension(40,200));
        modelo.setNumRows(0);
        modelo.addColumn("Nome");
        
        frame.setLayout(new BorderLayout());
        frame.add(BorderLayout.CENTER, consulta); //Adiciono a pergunta no frame..
        for (Membro membro : conexao.getInformacoesMensalidadeMembros()) {
			modelo.addRow(new Object[]{
                            membro.getNome_Membro()
                            });
        }
        frame.add(BorderLayout.SOUTH, scrollpane);
        frame.setVisible(true);
        frame.setSize(800,300);
        frame.setResizable(false);
        frame.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
    }

    
    public void CriaTabela4() throws ClassNotFoundException{
        JFrame frame = new JFrame();
        JLabel consulta = new JLabel("-- Liste o nome dos eventos, o local onde eles acontecerão e o nome do responsável por cada evento:");
        JTable tabelaBotao1 = new JTable (modelo);
        tabelaBotao1.setEnabled(false);
        scrollpane = new JScrollPane(tabelaBotao1);
        scrollpane.setPreferredSize(new Dimension(40,200));
        modelo.setNumRows(0);
        modelo.addColumn("Evento");
        modelo.addColumn("Local");
        modelo.addColumn("Membro");
        
        frame.setLayout(new BorderLayout());
        frame.add(BorderLayout.CENTER, consulta); //Adiciono a pergunta no frame..
        for (Evento evento : conexao.getInformacoesEventos()) {
			modelo.addRow(new Object[]{
                            evento.getNome_Evento(),
                            evento.getLocal_Evento(),
                            evento.getNome_Membro()
                            });
        }
        frame.add(BorderLayout.SOUTH, scrollpane);
        frame.setVisible(true);
        frame.setSize(800,300);
        frame.setResizable(false);
        frame.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        
        
    }
    
    
    public void CriaTabela5() throws ClassNotFoundException{
        JFrame frame = new JFrame();
        JLabel consulta = new JLabel("-- Informe o nome e quais os tipos de doações que os membros beneficiarios fizeram para a associação:");
        JTable tabelaBotao1 = new JTable (modelo);
        tabelaBotao1.setEnabled(false);
        scrollpane = new JScrollPane(tabelaBotao1);
        scrollpane.setPreferredSize(new Dimension(40,200));
        modelo.setNumRows(0);
        modelo.addColumn("Membro");
        modelo.addColumn("Tipo de Contribuição");
                
        frame.setLayout(new BorderLayout());
        frame.add(BorderLayout.CENTER, consulta); //Adiciono a pergunta no frame..
        for (TipoContribuicoes td : conexao.getInformacoesTipoDoacoes()) {
			modelo.addRow(new Object[]{
                            td.getNome_Membro(),
                            td.getTipo_contr()
                            });
        }
        frame.add(BorderLayout.SOUTH, scrollpane);
        frame.setVisible(true);
        frame.setSize(800,300);
        frame.setResizable(false);
        frame.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        
    }
    
    
    public void CriaTabela6() throws ClassNotFoundException{
        JFrame frame = new JFrame();
        JLabel consulta = new JLabel("-- Mostre a média das contribuições em dinheiro feitas por membros não efetivos:");
        JTable tabelaBotao1 = new JTable (modelo);
        tabelaBotao1.setEnabled(false);
        scrollpane = new JScrollPane(tabelaBotao1);
        scrollpane.setPreferredSize(new Dimension(40,200));
        modelo.setNumRows(0);
        modelo.addColumn("Média das Contribuições em Dinheiro");
                
        frame.setLayout(new BorderLayout());
        frame.add(BorderLayout.CENTER, consulta); //Adiciono a pergunta no frame..
        for (TipoContribuicoes td : conexao.getInformacoesMediaContr()) {
			modelo.addRow(new Object[]{
                            td.getMedia_Contribuicoes()
                            });
        }
        frame.add(BorderLayout.SOUTH, scrollpane);
        frame.setVisible(true);
        frame.setSize(800,300);
        frame.setResizable(false);
        frame.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        
    }
    
    
    public void CriaTabela7() throws ClassNotFoundException{
        JFrame frame = new JFrame();
        JLabel consulta = new JLabel("-- -- Mostre o nome de quem apoiou e o seu número de cadastro na associação, o tipo de apoio, e o evento que foi apoiado culturalmente:");
        JTable tabelaBotao1 = new JTable (modelo);
        tabelaBotao1.setEnabled(false);
        scrollpane = new JScrollPane(tabelaBotao1);
        scrollpane.setPreferredSize(new Dimension(40,200));
        modelo.setNumRows(0);
        modelo.addColumn("Cadastro");
        modelo.addColumn("Membro");
        modelo.addColumn("Descrição");
        modelo.addColumn("Evento");
        modelo.addColumn("Local do Evento");
                
        frame.setLayout(new BorderLayout());
        frame.add(BorderLayout.CENTER, consulta); //Adiciono a pergunta no frame..
        for (ApoioCultural ac : conexao.getInformacoesApoioCultural()) {
			modelo.addRow(new Object[]{
                            ac.getNum_Cadastro(),
                            ac.getNome_Membro(),
                            ac.getDescri_apoio_cultural(),
                            ac.getNome_Evento(),
                            ac.getLocal_Evento()
                            });
        }
        frame.add(BorderLayout.SOUTH, scrollpane);
        frame.setVisible(true);
        frame.setSize(800,300);
        frame.setResizable(false);
        frame.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
    }
    
    
    public void CriaTabela8() throws ClassNotFoundException{
        JFrame frame = new JFrame();
        JLabel consulta = new JLabel("-- Diga quais as regiões onde os membros moram (cidades) e informe a quantidade de membros que moram nas mesmas regiões:");
        JTable tabelaBotao1 = new JTable (modelo);
        tabelaBotao1.setEnabled(false);
        scrollpane = new JScrollPane(tabelaBotao1);
        scrollpane.setPreferredSize(new Dimension(40,200));
        modelo.setNumRows(0);
        modelo.addColumn("Cidade");
        modelo.addColumn("Quantidade de Membros");
                
        frame.setLayout(new BorderLayout());
        frame.add(BorderLayout.CENTER, consulta); //Adiciono a pergunta no frame..
        for (Membro membro : conexao.getInformacoesCidadesMembros()) {
			modelo.addRow(new Object[]{
                            membro.getCidade_Membro(),
                            membro.getQtd_Membros(),
                            });
        }
        frame.add(BorderLayout.SOUTH, scrollpane);
        frame.setVisible(true);
        frame.setSize(800,300);
        frame.setResizable(false);
        frame.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        
    }
    
    
    public void CriaTabela9() throws ClassNotFoundException{
        JFrame frame = new JFrame();
        JLabel consulta = new JLabel("-- Mostre os eventos abertos ao publico, a quantidade de participantes confirmados, o local e a data em que o evento irá ocorrer:");
        JTable tabelaBotao1 = new JTable(modelo);
        tabelaBotao1.setEnabled(false);
        scrollpane = new JScrollPane(tabelaBotao1);
        scrollpane.setPreferredSize(new Dimension(40,200));
        modelo.setNumRows(0);
        modelo.addColumn("Evento");
        modelo.addColumn("Quantidade de participantes");
        modelo.addColumn("Local");
        
                
        frame.setLayout(new BorderLayout());
        frame.add(BorderLayout.CENTER, consulta); //Adiciono a pergunta no frame..
        for (EventoAberto ea : conexao.getInformacoesEventoAberto()) {
			modelo.addRow(new Object[]{
                            ea.getNome_Evento(),
                            ea.getQtd_Participantes(),
                            ea.getLocal_Evento()
                            });
        }
        frame.add(BorderLayout.SOUTH, scrollpane);
        frame.setVisible(true);
        frame.setSize(800,300);
        frame.setResizable(false);
        frame.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
    }
    
    
    public void CriaTabela10() throws ClassNotFoundException{
        JFrame frame = new JFrame();
        JLabel consulta = new JLabel("-- Informe o num de telefone e o nome dos membros surdos, separados por um ' - ':");
        JTable tabelaBotao1 = new JTable(modelo);
        tabelaBotao1.setEnabled(false);
        scrollpane = new JScrollPane(tabelaBotao1);
        scrollpane.setPreferredSize(new Dimension(40,200));
        modelo.setNumRows(0);
        modelo.addColumn("Membro + Telefone");
        modelo.addColumn("Condição");
        
                
        frame.setLayout(new BorderLayout());
        frame.add(BorderLayout.CENTER, consulta); //Adiciono a pergunta no frame..
        for (Membro ea : conexao.getInformacoesTelMembros()) {
			modelo.addRow(new Object[]{
                            ea.getTel_Nome_Membro(),
                            ea.getCond_Membro()
                            });
        }
        frame.add(BorderLayout.SOUTH, scrollpane);
        frame.setVisible(true);
        frame.setSize(800,300);
        frame.setResizable(false);
        frame.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
    }
}
