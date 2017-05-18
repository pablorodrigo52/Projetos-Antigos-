-- Esquema "aulabd" --
CREATE SCHEMA PabloRodrigo_201320007420;
--

-- Domínios --
CREATE DOMAIN PabloRodrigo_201320007420.tipoNumCadastro AS INT;
CREATE DOMAIN PabloRodrigo_201320007420.tipoCodEvento AS INT; 
CREATE DOMAIN PabloRodrigo_201320007420.tipoCEP AS VARCHAR(8) DEFAULT '49000000'; -- É o cep 'default' de aracaju..
CREATE DOMAIN PabloRodrigo_201320007420.tipoCPF AS VARCHAR(11);


-- tabela associação --
CREATE TABLE PabloRodrigo_201320007420.cesaju(
	CNPJ_Assoc VARCHAR(18),
	end_Assoc VARCHAR(100) NOT NULL,
	num_reg_INSS INT NOT NULL UNIQUE,
	num_reg_Pref INT NOT NULL UNIQUE,
	PRIMARY KEY (CNPJ_Assoc)
);
-- fim tabela associação --
                      
-- tabela membro --
CREATE TABLE PabloRodrigo_201320007420.membro(
	num_Cadastro PabloRodrigo_201320007420.tipoNumCadastro,
	genero_Membro VARCHAR(1) NOT NULL CONSTRAINT verificaGenero CHECK (genero_membro = 'M' OR genero_membro = 'F'),
	cond_Membro VARCHAR(8) NOT NULL CONSTRAINT verificaCondicao CHECK (cond_Membro = 'Surdo' OR cond_Membro = 'Ouvinte'),
	email_Membro VARCHAR(45) NOT NULL,
	nome_Membro VARCHAR(50) NOT NULL,
	rua_Membro VARCHAR(45) NOT NULL,
	cidade_Membro VARCHAR(45) NOT NULL,
	estado_Membro VARCHAR(45) NOT NULL,
	cep_Membro PabloRodrigo_201320007420.tipoCEP NOT NULL,
	PRIMARY KEY (num_Cadastro)
);
CREATE TABLE PabloRodrigo_201320007420.membro_telefone(
	num_Telefone VARCHAR(18),
	num_cadastro PabloRodrigo_201320007420.tipoNumCadastro,
	PRIMARY KEY (num_Telefone, num_cadastro),
	FOREIGN KEY (num_cadastro) REFERENCES PabloRodrigo_201320007420.membro(num_cadastro) ON DELETE SET NULL ON UPDATE CASCADE
);
-- fim tabela membro --


-- relação de contribuição do membro com a associação --
CREATE TABLE PabloRodrigo_201320007420.contribuicao(
	tipo_Contr VARCHAR(100) NOT NULL,
	data_Contr DATE NOT NULL,
	cnpj_assoc VARCHAR(18),
	num_cadastro PabloRodrigo_201320007420.tipoNumCadastro,
	ID_Contr SERIAL,
	PRIMARY KEY(id_Contr, num_cadastro, cnpj_assoc),
	FOREIGN KEY (cnpj_assoc) REFERENCES PabloRodrigo_201320007420.cesaju(CNPJ_Assoc) ON DELETE SET NULL ON UPDATE CASCADE,
	FOREIGN KEY (num_cadastro) REFERENCES PabloRodrigo_201320007420.membro(num_cadastro) ON DELETE SET NULL ON UPDATE CASCADE
);
-- fim da relação --

-- filho direito de membro. (membro -> efetivo) --
CREATE TABLE PabloRodrigo_201320007420.efetivo(
	cpf_Efetivo PabloRodrigo_201320007420.tipoCPF,
	num_cadastro PabloRodrigo_201320007420.tipoNumCadastro,
	membro_Fundador BOOLEAN NOT NULL,
	membro_Honorario BOOLEAN NOT NULL,
	PRIMARY KEY (cpf_Efetivo, num_cadastro),
	FOREIGN KEY (num_cadastro) REFERENCES PabloRodrigo_201320007420.membro(num_cadastro) ON DELETE SET NULL ON UPDATE CASCADE
);
-- fim do filho d. --

-- filho esquerdo de membro. (beneficiario <- membro) --
CREATE TABLE PabloRodrigo_201320007420.beneficiario(
	num_cadastro PabloRodrigo_201320007420.tipoNumCadastro,
	PRIMARY KEY (num_cadastro),
	FOREIGN KEY (num_cadastro) REFERENCES PabloRodrigo_201320007420.membro(num_cadastro) ON DELETE SET NULL ON UPDATE CASCADE
);
-- fim do filho e. --

-- tabela Tipo de Evento --
CREATE TABLE PabloRodrigo_201320007420.tipodeevento(
	cod_TipodeEvento PabloRodrigo_201320007420.tipoCodEvento,
	nome_TipodeEvento VARCHAR(50) NOT NULL,
	descri_TipodeEvento VARCHAR(200) NOT NULL,
	PRIMARY KEY (cod_TipodeEvento)
);
-- fim tabela Tipo de Evento --

-- tabela Evento --
CREATE TABLE PabloRodrigo_201320007420.evento(
	cod_Evento PabloRodrigo_201320007420.tipoCodEvento UNIQUE,
	local_Evento VARCHAR(100) NOT NULL,
	hora_Evento VARCHAR(45) NOT NULL,
	data_inicioEvento DATE NOT NULL,
	data_fimEvento DATE,
	nome_Evento VARCHAR(50) NOT NULL,
	cod_TipodeEvento INT NOT NULL,
	cpf_Efetivo PabloRodrigo_201320007420.tipoCPF NOT NULL,
	num_cadastro PabloRodrigo_201320007420.tipoNumCadastro NOT NULL,
	PRIMARY KEY (cod_Evento, cod_TipodeEvento),
	FOREIGN KEY (cod_TipodeEvento) REFERENCES PabloRodrigo_201320007420.tipodeevento(cod_TipodeEvento) ON DELETE SET NULL,
	FOREIGN KEY (cpf_Efetivo, num_cadastro) REFERENCES PabloRodrigo_201320007420.efetivo(cpf_Efetivo, num_cadastro) ON DELETE SET NULL
);
-- fim tabela Evento --


-- tabela Apoio Cultural --
CREATE TABLE PabloRodrigo_201320007420.apoiocultural(
	cod_Evento PabloRodrigo_201320007420.tipoCodEvento,
	num_Cadastro PabloRodrigo_201320007420.tipoNumCadastro,
	CNPJ_Assoc VARCHAR(18),
	descri_apoio_cultural VARCHAR(100) NOT NULL,
	PRIMARY KEY (cod_Evento, num_Cadastro, CNPJ_Assoc),
	FOREIGN KEY (cod_Evento) REFERENCES PabloRodrigo_201320007420.evento(cod_Evento) ON DELETE SET NULL,
	FOREIGN KEY (num_Cadastro) REFERENCES PabloRodrigo_201320007420.membro(num_Cadastro) ON DELETE SET NULL,
	FOREIGN KEY (CNPJ_Assoc) REFERENCES PabloRodrigo_201320007420.cesaju(CNPJ_Assoc) ON DELETE SET NULL
);
-- fim Apoio Cultural --


-- filho esquerdo de evento (fechado <- evento) --
CREATE TABLE PabloRodrigo_201320007420.fechado(
	cod_Evento PabloRodrigo_201320007420.tipoCodEvento,
	qtd_Convites INT CHECK (qtd_Convites > 0),
	PRIMARY KEY (cod_Evento),
	FOREIGN KEY (cod_Evento) REFERENCES PabloRodrigo_201320007420.evento(cod_Evento) ON DELETE SET NULL
);
-- fim filho e. --


-- filho direito de evento (evento -> aberto) --
CREATE TABLE PabloRodrigo_201320007420.aberto(
	cod_Evento PabloRodrigo_201320007420.tipoCodEvento,
	qtd_Pessoas INT CHECK (qtd_Pessoas > 0),
	PRIMARY KEY (cod_Evento),
	FOREIGN KEY (cod_Evento) REFERENCES PabloRodrigo_201320007420.evento(cod_Evento) ON DELETE SET NULL
);
-- fim filho d. --

-- tabela peventoaberto --
CREATE TABLE PabloRodrigo_201320007420.peventoaberto(
	cod_Evento PabloRodrigo_201320007420.tipoCodEvento,
	num_Cadastro PabloRodrigo_201320007420.tipoNumCadastro,
	PRIMARY KEY(cod_Evento, num_Cadastro),
	FOREIGN KEY (cod_Evento) REFERENCES PabloRodrigo_201320007420.aberto(cod_Evento) ON DELETE SET NULL ON UPDATE CASCADE,
	FOREIGN KEY (num_Cadastro) REFERENCES PabloRodrigo_201320007420.membro(num_Cadastro) ON DELETE SET NULL
);
-- fim tablea peventoaberto --


-- tabela peventofechado --
CREATE TABLE PabloRodrigo_201320007420.peventofechado(
	cod_Evento PabloRodrigo_201320007420.tipoCodEvento,
	cpf_Efetivo PabloRodrigo_201320007420.tipoCPF,
	num_cadastro PabloRodrigo_201320007420.tipoNumCadastro,
	PRIMARY KEY(cod_Evento, num_cadastro, cpf_Efetivo),
	FOREIGN KEY (cod_Evento) REFERENCES PabloRodrigo_201320007420.fechado(cod_Evento) ON DELETE SET NULL ON UPDATE CASCADE,
	FOREIGN KEY (cpf_Efetivo, num_cadastro) REFERENCES PabloRodrigo_201320007420.efetivo(cpf_Efetivo, num_cadastro) ON DELETE SET NULL
);
-- fim tablea peventofechado --