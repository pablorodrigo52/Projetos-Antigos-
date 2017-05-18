import java.awt.BorderLayout;
import java.awt.Container;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;
import java.util.Vector;

import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JScrollPane;

public class AcoesBotao2 extends JFrame {

	private JList conteudo = new JList();

	public AcoesBotao2() {
		super("Ver empresas cadastradas");

		Container contentPane = getContentPane();
		contentPane.setLayout(new BorderLayout());
		conteudo.setListData(LerArquivo()); // ou recebe um object [] ou um
											// vector
		// aqui abaixo são as barras de rolagem..
		JScrollPane scrollPane = new JScrollPane(conteudo,
				JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,
				JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);

		contentPane.add(BorderLayout.CENTER, scrollPane); // adiciono tudo ao
															// container e torno
															// visible
		contentPane.setVisible(true);
	}

	public Object[] LerArquivo() {   // fazer  um actionListner pra JList
		List empresas = new LinkedList();
		try {
			File arquivo = new File("dataEmpresas.p");
			FileReader ler = new FileReader(arquivo);
			BufferedReader lerb = new BufferedReader(ler);
			String linha = lerb.readLine();
			while (linha != null) {
				empresas.add(linha);
				linha = lerb.readLine();
			}
			lerb.close(); // fecho o "canal"
			ler.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return empresas.toArray();
	}

}
