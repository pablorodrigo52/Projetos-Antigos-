/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Pablo Rodrigo
 */
public class TipoEvento {
    
    private int Cod_TipoEvento;
    private String Nome_TipoEvento;
    private String Descri_TipoEvento;
    
    
    
    public int getCod_TipoEvento(){
        return Cod_TipoEvento;
    }
    public void setCod_TipoEvento(int Cod_TipoEvento){
        this.Cod_TipoEvento = Cod_TipoEvento;
    }
    
    //---------------------------------------------------
    
    public String getNome_TipoEvento(){
        return Nome_TipoEvento;
    }
    public void setNome_TipoEvento(String Nome_TipoEvento){
        this.Nome_TipoEvento = Nome_TipoEvento;
    }
    
   //---------------------------------------------------
    
    public String getDescri_TipoEvento(){
        return Descri_TipoEvento;
    }
    public void setDescri_TipoEvento(String Descri_TipoEvento){
        this.Descri_TipoEvento = Descri_TipoEvento;
    }
}
