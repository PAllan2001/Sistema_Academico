CREATE DATABASE SistemaAcademico;
GO

USE SistemaAcademico;
GO
---------------------------------------------
CREATE TABLE Aluno (
    id_aluno INT IDENTITY(1,1) PRIMARY KEY,
    ra INT NOT NULL UNIQUE,
    nome_completo VARCHAR(100) NOT NULL
);
SELECT * FROM Aluno;

INSERT INTO Aluno (ra, nome_completo)
VALUES
(1001, 'Pablo Allan'),
(1002, 'Joao Silva'),
(1003, 'Maria Oliveira');

----------------------------------------------

CREATE TABLE Materia (
    id_materia INT IDENTITY(1,1) PRIMARY KEY,
    nome_materia VARCHAR(100) NOT NULL,
    carga_horaria INT NOT NULL
);

SELECT * FROM Materia;

INSERT INTO Materia (nome_materia, carga_horaria)
VALUES
('Programacao em C', 80),
('Banco de Dados', 80),
('Estrutura de Dados', 80),
('Sistemas Operacionais', 60);

-----------------------------------------------
CREATE TABLE Historico (
    id_historico INT IDENTITY(1,1) PRIMARY KEY,

    id_aluno INT NOT NULL,
    id_materia INT NOT NULL,

    nota DECIMAL(4,2) NOT NULL,

    CONSTRAINT FK_Historico_Aluno
        FOREIGN KEY (id_aluno)
        REFERENCES Aluno(id_aluno),

    CONSTRAINT FK_Historico_Materia
        FOREIGN KEY (id_materia)
        REFERENCES Materia(id_materia),

    CONSTRAINT UQ_Aluno_Materia
        UNIQUE (id_aluno, id_materia)
);

SELECT * FROM Historico;

INSERT INTO Historico (id_aluno, id_materia, nota)
VALUES
(1,1,8.5),
(1,2,7.8),
(1,3,6.2),

(2,1,5.5),
(2,2,8.0),

(3,2,9.5),
(3,4,8.8);

--------------------------------
--PESQUISAS

SELECT
    a.ra,
    a.nome_completo,
    m.nome_materia,
    h.nota
FROM Historico h
INNER JOIN Aluno a
    ON h.id_aluno = a.id_aluno
INNER JOIN Materia m
    ON h.id_materia = m.id_materia
ORDER BY a.nome_completo;

SELECT
    a.nome_completo,
    m.nome_materia,
    h.nota,
    CASE
        WHEN h.nota >= 7 THEN 'Aprovado'
        ELSE 'Reprovado'
    END AS Situacao
FROM Historico h
INNER JOIN Aluno a
    ON h.id_aluno = a.id_aluno
INNER JOIN Materia m
    ON h.id_materia = m.id_materia;

SELECT *
FROM Aluno
WHERE ra = 1001;

SELECT *
FROM Materia
WHERE nome_materia = 'Banco de Dados';

SELECT
    a.nome_completo,
    m.nome_materia,
    h.nota
FROM Historico h
INNER JOIN Aluno a
    ON h.id_aluno = a.id_aluno
INNER JOIN Materia m
    ON h.id_materia = m.id_materia
WHERE a.ra = 1001;

SELECT
    a.nome_completo,
    AVG(h.nota) AS Media
FROM Historico h
INNER JOIN Aluno a
    ON h.id_aluno = a.id_aluno
WHERE a.ra = 1001
GROUP BY a.nome_completo;

SELECT
    a.nome_completo,
    m.nome_materia,
    h.nota
FROM Historico h
INNER JOIN Aluno a
    ON h.id_aluno = a.id_aluno
INNER JOIN Materia m
    ON h.id_materia = m.id_materia
WHERE h.nota >= 7;

