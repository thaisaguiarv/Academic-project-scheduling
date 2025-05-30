*CRIAÇÃO DAS TABELEAS*

-- Tabela UNIDADE
CREATE TABLE UNIDADE (
    CNPJ NUMBER(14) PRIMARY KEY,
    ENDERECO VARCHAR2(80),
    CONTATO NUMBER(12)
);

-- Tabela PACIENTE
CREATE TABLE PACIENTE (
    IDPACIENTE NUMBER(10) PRIMARY KEY,
    CPF NUMBER(12),
    NOME VARCHAR2(40),
    DTNASCIMENTO DATE,
    EMAIL VARCHAR2(30),
    TELEFONE NUMBER(12)
);

-- Tabela UNI_PACIENTE
CREATE TABLE UNI_PACIENTE (
    CNPJ NUMBER(14),
    IDPACIENTE NUMBER(10),
    PRIMARY KEY (CNPJ, IDPACIENTE),
    FOREIGN KEY (CNPJ) REFERENCES UNIDADE(CNPJ),
    FOREIGN KEY (IDPACIENTE) REFERENCES PACIENTE(IDPACIENTE)
);

-- Tabela MEDICO
CREATE TABLE MEDICO (
    IDMEDICO NUMBER(10) PRIMARY KEY,
    CRM NUMBER(10),
    NOME VARCHAR2(40)
);

-- Tabela CONSULTA
CREATE TABLE CONSULTA (
    IDPACIENTE NUMBER(10),
    IDMEDICO NUMBER(10),
    DATA DATE,
    HORA VARCHAR2 (8),
    PRIMARY KEY (IDPACIENTE, IDMEDICO),
    FOREIGN KEY (IDPACIENTE) REFERENCES PACIENTE(IDPACIENTE),
    FOREIGN KEY (IDMEDICO) REFERENCES MEDICO(IDMEDICO)
);

-- Tabela ESPECIALIDADE
CREATE TABLE ESPECIALIDADE (
    IDESPECIALIDADE NUMBER(10) PRIMARY KEY,
    DESCRICAO VARCHAR2(30)
);

-- Tabela MED_ESPECIALIDADE 
CREATE TABLE MED_ESPECIALIDADE (
    IDMEDICO NUMBER(10),
    IDESPECIALIDADE NUMBER(10),
    PRIMARY KEY (IDMEDICO, IDESPECIALIDADE),
    FOREIGN KEY (IDMEDICO) REFERENCES MEDICO(IDMEDICO),
    FOREIGN KEY (IDESPECIALIDADE) REFERENCES ESPECIALIDADE(IDESPECIALIDADE)
);

INSERT INTO UNIDADE
(CNPJ, ENDERECO, CONTATO)
VALUES
(23210926000107, 'Rua Maria 58 - Parque dos Camargos ', 11986234872 );
INSERT INTO UNIDADE
(CNPJ, ENDERECO, CONTATO)
VALUES
(77873988000142, 'Avenida Ipiranga 678 - Jardim Paulista', 11983409120 );
INSERT INTO UNIDADE
(CNPJ, ENDERECO, CONTATO)
VALUES
(33387672000150, 'Rua Peixonalta 78 - Parque Almeida', 21967102209 );

INSERT INTO PACIENTE
(IDPACIENTE, CPF, NOME, DTNASCIMENTO, EMAIL, TELEFONE)
VALUES
(12, 46895702896, 'VANESSA LOPES RAMOS', TO_DATE('25/09/1997', 'DD/MM/YYYY'), 'VANRAMOS@GMAIL.COM', 11987562301);

INSERT INTO PACIENTE
(IDPACIENTE, CPF, NOME, DTNASCIMENTO, EMAIL, TELEFONE)
VALUES
(25, 97653458965, 'DANIEL OLIVEIRA SILVA', TO_DATE('08/12/1987', 'DD/MM/YYYY'), 'DANELSILVA@OUTLOOK.COM', 19965782349);

INSERT INTO PACIENTE
(IDPACIENTE, CPF, NOME, DTNASCIMENTO, EMAIL, TELEFONE)
VALUES
(73, 43597037875, 'LARISSA ALMEIDA SANTOS', TO_DATE('28/02/2001', 'DD/MM/YYYY'), 'LARIALSAN@HOTMAIL.COM', 21998347160);

INSERT INTO UNI_PACIENTE
(CNPJ, IDPACIENTE)
VALUES
(33387672000150, 12);

INSERT INTO UNI_PACIENTE
(CNPJ, IDPACIENTE)
VALUES
(23210926000107, 73);

INSERT INTO UNI_PACIENTE
(CNPJ, IDPACIENTE)
VALUES
(77873988000142, 25);

INSERT INTO MEDICO
(IDMEDICO, CRM, NOME)
VALUES
(89905, 198084, 'JOSE AZEVEDO LEMES');

INSERT INTO MEDICO
(IDMEDICO, CRM, NOME)
VALUES
(89908, 178094, 'ALINE MACEDO SANTOS' );

INSERT INTO MEDICO
(IDMEDICO, CRM, NOME)
VALUES
(89910, 150956, 'LETICIA LEITAO DA SILVA' );

INSERT INTO CONSULTA
(IDPACIENTE, IDMEDICO, DATA, HORA)
VALUES
(25, 89905,TO_DATE('23/02/2025', 'DD/MM/YYYY'), '13:25');

INSERT INTO CONSULTA
(IDPACIENTE, IDMEDICO, DATA, HORA)
VALUES
(73,89908, TO_DATE('17/05/2025','DD/MM/YYYY'),'10:30');

INSERT INTO CONSULTA
(IDPACIENTE, IDMEDICO, DATA, HORA)
VALUES
(12, 89910, TO_DATE('20/04/2025','DD/MM/YYYY'),'10:30');

INSERT INTO ESPECIALIDADE
(IDESPECIALIDADE, DESCRICAO)
VALUES
(60987,'CARDIOLOGIA');

INSERT INTO ESPECIALIDADE
(IDESPECIALIDADE, DESCRICAO)
VALUES
(60995,'PSIQUIATRIA');

INSERT INTO ESPECIALIDADE
(IDESPECIALIDADE, DESCRICAO)
VALUES
(60968,'DERMATOLOGIA');

INSERT INTO MED_ESPECIALIDADE
(IDMEDICO, IDESPECIALIDADE)
VALUES
(89908, 60987);

INSERT INTO MED_ESPECIALIDADE
(IDMEDICO, IDESPECIALIDADE)
VALUES
(89910, 60995);

INSERT INTO MED_ESPECIALIDADE
(IDMEDICO, IDESPECIALIDADE)
VALUES
(89905, 60968);




