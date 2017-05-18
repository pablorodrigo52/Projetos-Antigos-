/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Pablo Rodrigo
 */
public class TipoContribuicoes {
    private String nome_Membro;
    private String tipo_contr;
    private float media_Contribuicoes;
    
    
    public String getNome_Membro(){
        return nome_Membro;
    }
    public void setNome_Membro(String nome_Membro){
        this.nome_Membro = nome_Membro;
    }
    
    public float getMedia_Contribuicoes(){
        return media_Contribuicoes;
    }
    public void setMedia_Contribuicoes(float media_Contribuicoes){
        this.media_Contribuicoes = media_Contribuicoes;
    }
    
    public String getTipo_contr(){
        return tipo_contr;
    }
    public void setTipo_contr(String tipo_contr){
        this.tipo_contr = tipo_contr;
    }
}
