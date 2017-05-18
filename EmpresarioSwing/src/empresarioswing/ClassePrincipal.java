import javax.swing.JFrame;

public class ClassePrincipal {
	public static void main(String[] args) {
		EmpresarioSwing empresarioswing = new EmpresarioSwing(); // instancio a classe empresarioswing.. 
		
		// Aqui abaixo são algumas caracteristicas da janela de Empresario.. 
		empresarioswing.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // ao fechar, encerra o programa
		empresarioswing.setSize(540, 220); // o tamanho da tela.. 
		empresarioswing.setResizable(false);  // não pode ser redimensionavel
		empresarioswing.setVisible(true);  // tornei ela visivel..
	
	}
}
