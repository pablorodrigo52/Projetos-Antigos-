
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;
import javax.swing.JOptionPane;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Pablo Rodrigo
 */
public class ConexaoBD {
   
    private String SQL;
    private final String url = "jdbc:postgresql://10.27.133.186:5432/bd_trabalho";  
    private final String usuario = "aluno";  
    private final String senha = "aluno";
    
    Connection con = null;         
    PreparedStatement stm = null; 
    ResultSet rs = null;
    
    public List<Membro> getInformacoesMembros(String categoria) throws ClassNotFoundException{
    
        SQL = null;
        
        //Trato em qual tabela vai ser a consulta..
        switch (categoria) {
            case "efetivo":
                SQL = "SELECT num_Cadastro, nome_Membro, email_Membro, cond_Membro, cep_Membro, rua_Membro"
                        + " FROM (pablorodrigo_201320007420.membro NATURAL JOIN pablorodrigo_201320007420.efetivo)"
                        + " WHERE membro_Fundador = FALSE AND membro_Honorario = FALSE;";
                break;
            case "beneficiario":
                SQL = "SELECT num_Cadastro, nome_Membro, email_Membro, cond_Membro, cep_Membro, rua_Membro"
                        + " FROM (pablorodrigo_201320007420.membro NATURAL JOIN pablorodrigo_201320007420.beneficiario);";
                break;
            case "honorario":
                SQL = "SELECT num_Cadastro, nome_Membro, email_Membro, cond_Membro, cep_Membro, rua_Membro"
                        + " FROM (pablorodrigo_201320007420.membro NATURAL JOIN pablorodrigo_201320007420.efetivo)"
                        + " WHERE membro_Fundador = FALSE AND membro_Honorario = TRUE;";
                break;
            default:
                break;
        }
        
        //Inicio da conexão... 
        Class.forName("org.postgresql.Driver");
        ArrayList<Membro> informacoes = new ArrayList<>();

        try{
            con = DriverManager.getConnection(url, usuario, senha);
            stm = con.prepareStatement(SQL);
            rs = stm.executeQuery();
            
            while (rs.next()){
                Membro membro = new Membro();

                membro.setNum_Cadastro(rs.getInt("num_Cadastro"));
                membro.setNome_Membro(rs.getString("nome_Membro"));
                membro.setEmail_Membro(rs.getString("email_Membro"));
                membro.setCond_Membro(rs.getString("cond_Membro"));
                membro.setCep_Membro(rs.getString("cep_Membro"));
                membro.setRua_Membro(rs.getString("rua_Membro"));
                informacoes.add(membro);
            }
            con.close();
            }catch (Exception e) { //ATUALIZAÇÃO.. Corrigido o erro ao listar as tabelas...
			JOptionPane.showMessageDialog(null, "Erro ao listar as informações do banco de dados! >> " + e.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
	    }
	    return informacoes;
            
    }

    public List<TipoEvento> getInformacoesTipoEvento() throws ClassNotFoundException {
        
        ArrayList<TipoEvento> informacoes = new ArrayList<>();
        SQL = "SELECT nome_tipodeevento, descri_tipodeevento"
            + " FROM pablorodrigo_201320007420.tipodeevento"
            + " ORDER BY nome_tipodeevento;";
        
        Class.forName("org.postgresql.Driver");
        try{
            con = DriverManager.getConnection(url, usuario, senha);
            stm = con.prepareStatement(SQL);
            rs = stm.executeQuery();
            
            while (rs.next()){
                TipoEvento tipo = new TipoEvento();
                
                //tipo.setCod_TipoEvento(rs.getInt("cod_tipodeevento"));
                tipo.setNome_TipoEvento(rs.getString("nome_tipodeevento"));
                tipo.setDescri_TipoEvento(rs.getString("descri_tipodeevento"));
                informacoes.add(tipo);
            }
            con.close();
            }catch (Exception e) { //ATUALIZAÇÃO.. Corrigido o erro ao listar as tabelas...
			JOptionPane.showMessageDialog(null, "Erro ao listar as informações do banco de dados! >> " + e.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
	    }
	    return informacoes;
    }

    public List<EventoLocalCesaju> getInformacoesEventoCesaju() throws ClassNotFoundException{
        
        ArrayList<EventoLocalCesaju> informacoes = new ArrayList<>();
        SQL = "SELECT nome_evento, local_evento, hora_evento"
            + " FROM pablorodrigo_201320007420.evento"
            + " WHERE local_evento = 'CESAJU';";
        
        Class.forName("org.postgresql.Driver");
        try{
            con = DriverManager.getConnection(url, usuario, senha);
            stm = con.prepareStatement(SQL);
            rs = stm.executeQuery();
            
            while (rs.next()){
                EventoLocalCesaju localCesaju = new EventoLocalCesaju();
                
                //tipo.setCod_TipoEvento(rs.getInt("cod_tipodeevento"));
                localCesaju.setNome_Evento(rs.getString("nome_evento"));
                localCesaju.setLocal_Evento(rs.getString("local_evento"));
                localCesaju.setData_Evento(rs.getString("hora_evento"));
                informacoes.add(localCesaju);
            }
            con.close();
            }catch (Exception e) { //ATUALIZAÇÃO.. Corrigido o erro ao listar as tabelas...
			JOptionPane.showMessageDialog(null, "Erro ao listar as informações do banco de dados! >> " + e.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
	    }
	    return informacoes;
    }
    
    public List<Membro> getInformacoesMensalidadeMembros () throws ClassNotFoundException {
        
        ArrayList<Membro> informacoes = new ArrayList<>();
        SQL = "SELECT DISTINCT nome_Membro "
            + "FROM pablorodrigo_201320007420.membro "
            + "JOIN pablorodrigo_201320007420.contribuicao USING (num_cadastro) "
            + "WHERE tipo_contr LIKE 'Mensal%';";
        
        Class.forName("org.postgresql.Driver");
        
        try{
            con = DriverManager.getConnection(url, usuario, senha);
            stm = con.prepareStatement(SQL);
            rs = stm.executeQuery();
            
            while (rs.next()){
                Membro membro = new Membro();
                membro.setNome_Membro(rs.getString("nome_Membro"));
                informacoes.add(membro);
            }
            con.close();
            }catch (Exception e) { //ATUALIZAÇÃO.. Corrigido o erro ao listar as tabelas...
			JOptionPane.showMessageDialog(null, "Erro ao listar as informações do banco de dados! >> " + e.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
	    }
	    return informacoes;
    }
    
    public List<Evento> getInformacoesEventos () throws ClassNotFoundException{
        
        ArrayList<Evento> informacoes = new ArrayList<>();
        SQL = "SELECT nome_Evento, local_Evento, nome_Membro "
                + "FROM pablorodrigo_201320007420.membro "
                + "NATURAL JOIN pablorodrigo_201320007420.evento "
                + "ORDER BY nome_Evento;";
        
         Class.forName("org.postgresql.Driver");
        
        try{
            con = DriverManager.getConnection(url, usuario, senha);
            stm = con.prepareStatement(SQL);
            rs = stm.executeQuery();
            
            while (rs.next()){
                Evento evento = new Evento();
                Membro membro = new Membro();
                evento.setNome_Evento(rs.getString("nome_evento"));
                evento.setLocal_Evento(rs.getString("local_evento"));
                evento.setNome_Membro(rs.getString("nome_membro"));
                
                informacoes.add(evento);
            }
            con.close();
            }catch (Exception e) { //ATUALIZAÇÃO.. Corrigido o erro ao listar as tabelas...
			JOptionPane.showMessageDialog(null, "Erro ao listar as informações do banco de dados! >> " + e.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
	    }
	    return informacoes;
    }
    
    public List<TipoContribuicoes> getInformacoesTipoDoacoes () throws ClassNotFoundException{
        
        ArrayList<TipoContribuicoes> informacoes = new ArrayList<>();
        SQL = "SELECT nome_Membro, tipo_contr "
                + "FROM pablorodrigo_201320007420.membro m "
                + "NATURAL JOIN pablorodrigo_201320007420.beneficiario b "
                + "JOIN pablorodrigo_201320007420.contribuicao c ON b.num_cadastro = c.num_cadastro;";
        
         Class.forName("org.postgresql.Driver");
        
        try{
            con = DriverManager.getConnection(url, usuario, senha);
            stm = con.prepareStatement(SQL);
            rs = stm.executeQuery();
            
            while (rs.next()){
                TipoContribuicoes td = new TipoContribuicoes();
                td.setNome_Membro(rs.getString("nome_membro"));
                td.setTipo_contr(rs.getString("tipo_contr"));
                
                informacoes.add(td);
            }
            con.close();
            }catch (Exception e) { //ATUALIZAÇÃO.. Corrigido o erro ao listar as tabelas...
			JOptionPane.showMessageDialog(null, "Erro ao listar as informações do banco de dados! >> " + e.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
	    }
	    return informacoes;
    }
    
    public List<TipoContribuicoes> getInformacoesMediaContr() throws ClassNotFoundException{
       
        ArrayList<TipoContribuicoes> informacoes = new ArrayList<>();
        SQL = "SELECT AVG(CAST(valor AS INT)) AS media_contribuicoes "
                + "FROM (SELECT SUBSTRING(tipo_contr, 3,3) AS valor "
                + "      FROM pablorodrigo_201320007420.contribuicao "
                + "      WHERE tipo_contr LIKE 'R$%') AS subs_valores;";
        
         Class.forName("org.postgresql.Driver");
        
        try{
            con = DriverManager.getConnection(url, usuario, senha);
            stm = con.prepareStatement(SQL);
            rs = stm.executeQuery();
            
            while (rs.next()){
                TipoContribuicoes td = new TipoContribuicoes();
                td.setMedia_Contribuicoes(rs.getFloat("media_contribuicoes"));
                informacoes.add(td);
            }
            con.close();
            }catch (Exception e) { //ATUALIZAÇÃO.. Corrigido o erro ao listar as tabelas...
			JOptionPane.showMessageDialog(null, "Erro ao listar as informações do banco de dados! >> " + e.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
	    }
	    return informacoes;
    }
    
    public List<ApoioCultural> getInformacoesApoioCultural() throws ClassNotFoundException{
        
        
        ArrayList<ApoioCultural> informacoes = new ArrayList<> ();
        SQL = "SELECT num_cadastro, nome_membro, descri_apoio_cultural, nome_evento, local_evento "
            + "FROM (SELECT m.num_cadastro, m.nome_membro, ap.descri_apoio_cultural, e.nome_evento, e.local_evento "
                + "  FROM pablorodrigo_201320007420.membro m  "
                + "  NATURAL JOIN pablorodrigo_201320007420.apoiocultural ap "
                + " JOIN pablorodrigo_201320007420.evento e USING (cod_evento)) AS aux_table"
                + " ORDER BY nome_membro";
        
         Class.forName("org.postgresql.Driver");
        
        try{
            con = DriverManager.getConnection(url, usuario, senha);
            stm = con.prepareStatement(SQL);
            rs = stm.executeQuery();
            
            while (rs.next()){
                ApoioCultural ac = new ApoioCultural();
                ac.setNum_Cadastro(rs.getInt("num_cadastro"));
                ac.setNome_Membro(rs.getString("nome_membro"));
                ac.setDescri_apoio_cultural(rs.getString("descri_apoio_cultural"));
                ac.setNome_Evento(rs.getString("nome_evento"));
                ac.setLocal_Evento(rs.getString("local_evento"));
                informacoes.add(ac);
            }
            con.close();
            }catch (Exception e) { //ATUALIZAÇÃO.. Corrigido o erro ao listar as tabelas...
			JOptionPane.showMessageDialog(null, "Erro ao listar as informações do banco de dados! >> " + e.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
	    }
	    return informacoes;
    }
    
    public List<Membro> getInformacoesCidadesMembros() throws ClassNotFoundException{
        ArrayList<Membro> informacoes = new ArrayList<>();
        SQL = "SELECT cidade_membro, count(nome_membro) AS qtd_membros "
            + "FROM pablorodrigo_201320007420.membro "
            + "GROUP BY cidade_membro ORDER BY qtd_membros DESC ";
        
         Class.forName("org.postgresql.Driver");
        
        try{
            con = DriverManager.getConnection(url, usuario, senha);
            stm = con.prepareStatement(SQL);
            rs = stm.executeQuery();
            
            while (rs.next()){
                Membro membro = new Membro();
                membro.setCidade_Membro(rs.getString("cidade_membro"));
                membro.setQtd_Membros(rs.getInt("qtd_membros"));
                informacoes.add(membro);
            }
            con.close();
            }catch (Exception e) { //ATUALIZAÇÃO.. Corrigido o erro ao listar as tabelas...
			JOptionPane.showMessageDialog(null, "Erro ao listar as informações do banco de dados! >> " + e.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
	    }
	    return informacoes;
        
        
    }
    
    public List<EventoAberto> getInformacoesEventoAberto() throws ClassNotFoundException{
        ArrayList<EventoAberto> informacoes = new ArrayList<>();
        SQL = "SELECT e.nome_evento, count(m.nome_membro) AS qtd_participantes, e.local_evento "
            + "FROM ( pablorodrigo_201320007420.evento e JOIN pablorodrigo_201320007420.aberto a USING (cod_evento)) "
            + "JOIN ( pablorodrigo_201320007420.membro m JOIN pablorodrigo_201320007420.peventoaberto pea ON (m.num_cadastro = pea.num_cadastro) ) USING (cod_evento) "
            + "GROUP BY pea.cod_evento, e.nome_evento, e.local_evento "
            + "ORDER BY e.nome_evento ";
        
         Class.forName("org.postgresql.Driver");
        
        try{
            con = DriverManager.getConnection(url, usuario, senha);
            stm = con.prepareStatement(SQL);
            rs = stm.executeQuery();
            
            while (rs.next()){
                EventoAberto ea = new EventoAberto();
                ea.setNome_Evento(rs.getString("nome_evento"));
                ea.setQtd_Participantes(rs.getInt("qtd_participantes"));
                ea.setLocal_Evento(rs.getString("local_evento"));
                informacoes.add(ea);
            }
            con.close();
            }catch (Exception e) { //ATUALIZAÇÃO.. Corrigido o erro ao listar as tabelas...
			JOptionPane.showMessageDialog(null, "Erro ao listar as informações do banco de dados! >> " + e.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
	    }
	    return informacoes;
    }
    
    public List<Membro> getInformacoesTelMembros() throws ClassNotFoundException{
        ArrayList<Membro> informacoes = new ArrayList<>();
        SQL = "SELECT nome_membro ||' - '|| num_telefone AS nome_telefone, cond_membro "
            + "FROM pablorodrigo_201320007420.membro  "
            + "JOIN (SELECT num_telefone, num_cadastro "
            + "FROM pablorodrigo_201320007420.membro_telefone) AS table_aux USING (num_cadastro) "
            + "WHERE cond_membro = 'Surdo' "
            + "ORDER BY nome_membro;";
        
         Class.forName("org.postgresql.Driver");
        
        try{
            con = DriverManager.getConnection(url, usuario, senha);
            stm = con.prepareStatement(SQL);
            rs = stm.executeQuery();
            
            while (rs.next()){
                Membro ea = new Membro();
                ea.setTel_Nome_Membro(rs.getString("nome_telefone"));
                ea.setCond_Membro(rs.getString("cond_membro"));
                informacoes.add(ea);
            }
            con.close();
            }catch (Exception e) { //ATUALIZAÇÃO.. Corrigido o erro ao listar as tabelas...
			JOptionPane.showMessageDialog(null, "Erro ao listar as informações do banco de dados! >> " + e.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
	    }
	    return informacoes;
    }
    
}
