/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Pablo Rodrigo
 */
public class EventoAberto {
    
    private String nome_evento;
    private int qtd_participantes;
    private String local_Evento;
    
    
    public String getNome_Evento(){
        return nome_evento;
    }
    public void setNome_Evento(String nome_evento){
        this.nome_evento = nome_evento;
    }
    
    
    public int getQtd_Participantes(){
        return qtd_participantes;
    }
    public void setQtd_Participantes(int qtd_participantes){
        this.qtd_participantes = qtd_participantes;
    }
    
    
    public String getLocal_Evento(){
        return local_Evento;
    }
    public void setLocal_Evento(String local_Evento){
        this.local_Evento = local_Evento;
    }
}
