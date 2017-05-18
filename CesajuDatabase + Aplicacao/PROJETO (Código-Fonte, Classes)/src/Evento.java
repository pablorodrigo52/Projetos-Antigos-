
import java.sql.Timestamp;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Pablo Rodrigo
 */
public class Evento {
    
    private int Cod_Evento;
    public String Nome_Membro;
    private String Local_Evento;
    private String Hora_Evento;
    private Timestamp Data_Evento;
    private String Nome_Evento;
    private int Cod_TipoDeEvent;
    private int CPF_Efetivo;
    private int Membro_num_Cadastro;
    
    
    public int getCod_Evento(){
        return Cod_Evento;
    }
    public void setCod_Evento(int Cod_Evento){
        this.Cod_Evento = Cod_Evento;
    }
    
   
    public String getNome_Membro(){
        return Nome_Membro;
    }
    public void setNome_Membro(String Nome_Membro){
        this.Nome_Membro = Nome_Membro;
    }
    
    
    
    public String getLocal_Evento(){
        return Local_Evento;
    }
    public void setLocal_Evento(String Local_Evento){
        this.Local_Evento = Local_Evento;
    }
        
    
    public Timestamp getData_Evento(){
        return Data_Evento;
    }
    public void setData_Evento(Timestamp Data_Evento){
        this.Data_Evento = Data_Evento;
    }
    
    
    public String getNome_Evento(){
        return Nome_Evento;
    }
    public void setNome_Evento(String Nome_Evento){
        this.Nome_Evento = Nome_Evento;
    }

    
    public int getCod_TipoDeEvent(){
        return Cod_TipoDeEvent;
    }
    public void setCod_TipoDeEvent(int Cod_TipoDeEvent){
        this.Cod_TipoDeEvent = Cod_TipoDeEvent;
    }
    
    
    public int getCPF_Efetivo(){
        return CPF_Efetivo;
    }
    public void setCPF_Efetivo(int CPF_Efetivo){
        this.CPF_Efetivo = CPF_Efetivo;
    }
    
    
    public int getMembro_num_Cadastro(){
        return Membro_num_Cadastro;
    }
    public void setMembro_num_Cadastro(int Membro_num_Cadastro){
        this.Membro_num_Cadastro = Membro_num_Cadastro;
    }
}
