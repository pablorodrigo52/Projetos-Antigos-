/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Pablo Rodrigo
 */
public class Associacao {
    
    private String CNPJ_Assoc;
    private String End_Assoc;
    private int Num_Reg_INSS;
    private int Num_Reg_Pref;
    
    
    public String getCNPJ_Assoc(){
        return CNPJ_Assoc;
    }
    public void setCNPJ_Assoc(String CNPJ_Assoc){
        this.CNPJ_Assoc = CNPJ_Assoc;
    }
    
    // -------------------------------------------- 
    
    public String getEnd_Assoc(){
        return End_Assoc;
    }
    public void setEnd_Assoc(String End_Assoc){
        this.End_Assoc = End_Assoc;
    }
    
    // -------------------------------------------- 
    
    public int getNum_Reg_INSS(){
        return Num_Reg_INSS;
    }
    public void setNum_Reg_INSS(int Num_Reg_INSS){
        this.Num_Reg_INSS = Num_Reg_INSS;
    }
    
    // -------------------------------------------- 
    
    public int getNum_Reg_Pref(){
        return Num_Reg_Pref;
    }
    public void setNum_Reg_Pref(int Num_Reg_Pref){
        this.Num_Reg_Pref = Num_Reg_Pref;
    }
}
