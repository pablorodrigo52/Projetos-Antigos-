-- Informe os tipos de eventos existentes
SELECT nome_tipodeevento, descri_tipodeevento
FROM pablorodrigo_201320007420.tipodeevento
ORDER BY nome_tipodeevento;


-- Informe o nome e a hora dos eventos que acontecerão no local da associação CESAJU
SELECT nome_evento, local_evento, hora_evento
FROM pablorodrigo_201320007420.evento
WHERE local_evento = 'CESAJU';


-- Selecione todos os membros que ja pagaram mensalidade para a associação alguma vez, sem repetição de nomes
SELECT DISTINCT nome_Membro 
FROM pablorodrigo_201320007420.membro 
JOIN pablorodrigo_201320007420.contribuicao USING (num_cadastro)
WHERE tipo_contr LIKE 'Mensal%';


-- Liste o nome dos eventos, o local onde eles acontecerão e o nome do responsável por cada evento
SELECT nome_Evento, local_Evento ,nome_Membro 
FROM pablorodrigo_201320007420.membro
NATURAL JOIN pablorodrigo_201320007420.evento
ORDER BY nome_Evento;


-- Informe o nome e quais os tipos de doações que os membros beneficiarios fizeram para a associação
SELECT nome_Membro, tipo_contr 
FROM pablorodrigo_201320007420.membro m 
NATURAL JOIN pablorodrigo_201320007420.beneficiario b
JOIN pablorodrigo_201320007420.contribuicao c ON b.num_cadastro = c.num_cadastro;


-- Mostre a média das contribuições em dinheiro feitas por membros não efetivos
SELECT AVG(CAST(valor AS INT)) AS media_contribuicoes  -- Eu armazenei as contribuições como VARCHAR pois os 'doadores' não necessariamente precisam contribuir com dinheiro
FROM (SELECT SUBSTRING(tipo_contr, 3,3) AS valor       -- então tive que fazer o cast de algumas contribuiçoes para INT. Elas estão armazenadas da forma 'R$XX', então, tive que 
      FROM pablorodrigo_201320007420.contribuicao      -- usar substring para quebrar a string onde eu queria, que é o valor "XX".
      WHERE tipo_contr LIKE 'R$%') AS subs_valores;


-- Mostre o nome de quem apoiou e o seu número de cadastro na associação, o tipo de apoio, e o evento que foi apoiado culturalmente e onde ele ocorrerá
SELECT num_cadastro, nome_membro, descri_apoio_cultural, nome_evento, local_evento
FROM (SELECT m.num_cadastro, m.nome_membro, ap.descri_apoio_cultural, e.nome_evento, e.local_evento
      FROM pablorodrigo_201320007420.membro m 
      NATURAL JOIN pablorodrigo_201320007420.apoiocultural ap 
      JOIN pablorodrigo_201320007420.evento e USING (cod_evento)) AS aux_table
ORDER BY nome_membro


-- Diga quais as regiões onde os membros moram (cidades) e informe a quantidade de membros que moram nas mesmas regiões
SELECT cidade_membro, count(nome_membro) AS qtd_membros
FROM pablorodrigo_201320007420.membro 
GROUP BY cidade_membro ORDER BY qtd_membros DESC


-- Mostre os eventos abertos ao publico, a quantidade de participantes confirmados, o local e a data em que o evento irá ocorrer.
SELECT e.nome_evento, count(m.nome_membro) AS qtd_participantes, e.local_evento
FROM ( pablorodrigo_201320007420.evento e JOIN pablorodrigo_201320007420.aberto a USING (cod_evento) ) 
JOIN ( pablorodrigo_201320007420.membro m JOIN pablorodrigo_201320007420.peventoaberto pea ON (m.num_cadastro = pea.num_cadastro) ) USING (cod_evento)
GROUP BY pea.cod_evento, e.nome_evento, e.local_evento
ORDER BY e.nome_evento


-- Informe o num de telefone e o nome dos membros surdos, separados por um ' - ', informe também a condição do membro para verificação 
SELECT nome_membro ||' - '|| num_telefone AS nome_telefone, cond_membro
FROM pablorodrigo_201320007420.membro 
JOIN (SELECT num_telefone, num_cadastro
      FROM pablorodrigo_201320007420.membro_telefone) AS table_aux USING (num_cadastro)
WHERE cond_membro = 'Surdo'
ORDER BY nome_membro;