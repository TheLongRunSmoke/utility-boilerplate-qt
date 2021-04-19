#pragma once

#include <QWidget>
#include "ui_TextEditor.h"

class TextEditor : public QWidget
{
	Q_OBJECT

public:
	explicit TextEditor(QWidget *parent = Q_NULLPTR);
	~TextEditor() override;
	void setText(const QString& text);
	QString getText();
	bool isModified();
	void clear();

private:
	Ui::TextEditor ui;
};
