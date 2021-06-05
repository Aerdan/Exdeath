/*
 * Copyright (c) 2021, Sheila Aman.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of the software nor the
 *      names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "exdeath.hh"
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <climits>

Exdeath::Exdeath(QSettings *cfg, QWidget *parent) : QWidget(parent) {
	error = new QErrorMessage();
	filename = nullptr;
	_cfg = cfg;

	layApp = new QVBoxLayout(this);
	layColumns = new QHBoxLayout(this);
	layApp->addLayout(layColumns);
	layColumn2 = new QVBoxLayout(this);

	initMain();
	initInnates();
	initMulti();
	layColumns->addLayout(layColumn2);

	initConfig();

	connect(btnROM, &QPushButton::clicked, this, &Exdeath::btnROM_clicked);
	connect(btnApply, &QPushButton::clicked, this, &Exdeath::btnApply_clicked);
	connect(btnSave, &QPushButton::clicked, this, &Exdeath::btnSave_clicked);
}

Exdeath::~Exdeath() {}

void Exdeath::initMain(void) {
	layMain = new QGridLayout(this);
	layMode = new QVBoxLayout(this);
	grpMain = new QGroupBox("Main");
	grpMain->setLayout(layMain);
	layColumns->addWidget(grpMain);

	txtROM       = new QLabel("ROM:");
	txtMode      = new QLabel("Mode:");
	txtPortraits = new QLabel("FFT-style Portraits:");
	txtSound     = new QLabel("Sound Restoration:");
	txtSound->setToolTip("Requires GBA BIOS if using VisualBoyAdvance");
	txtSeed      = new QLabel("Seed:");
	txtNED       = new QLabel("Neo ExDeath:");

	btnROM   = new QPushButton("Select ROM");
	btnApply = new QPushButton("Apply");
	layApp->addWidget(btnApply);
	btnSave  = new QPushButton("Save Config");

	selMode = new QComboBox();
	selMode->addItem("Base");
	selMode->addItem("Randomizer", "rando/fixmagic.ips");
	selMode->addItem("Unlocked Jobs", "unlock.ips");
	selMode->addItem("Balance", "balance.ips");
	selMode->addItem("Custom Classes", "custom_classes.ips");
	selMode->addItem("Waddler Rebalance", "waddle.ips");

	chkPortraits = new QCheckBox("Yes");
	chkSound     = new QCheckBox("Yes");

	numSeed = new QSpinBox();
	numSeed->setRange(0, INT_MAX);
	// provide a default value so it's not just 0 all the time
	numSeed->setValue(time(NULL) / 3600);

	selNED = new QComboBox();
	selNED->addItem("Random");
	selNED->addItem("Vanilla");
	selNED->setCurrentIndex(1);
	selNED->addItem("Barf", "barf.ips");
	selNED->addItem("Cactuar", "cactuar.ips");
	selNED->addItem("Chain Chomp", "chomp.ips");
	selNED->addItem("Classic", "classic.ips");
	selNED->addItem("Chaos", "chaos.ips");
	selNED->addItem("Doomtrain", "train.ips");
	selNED->addItem("Flammie (1)", "flammie1.ips");
	selNED->addItem("Flammie (2)", "flammie2.ips");
	selNED->addItem("Giant Beak", "giantbeak.ips");
	selNED->addItem("Godzilla", "godzilla.ips");
	selNED->addItem("Lavos Spawn", "lavos-spawn.ips");
	selNED->addItem("Kefka", "kefka.ips");
	selNED->addItem("MechaGodzilla", "mechagodzilla.ips");
	selNED->addItem("Metroid", "metroid.ips");
	selNED->addItem("Neo X Death", "neo-x-death.ips");
	selNED->addItem("Neon ExDeath", "fancy.ips");
	selNED->addItem("Puzzle & Dragon", "pad.ips");
	selNED->addItem("Romancing SaGa 3 Boss", "rs3boss.ips");
	selNED->addItem("Shaq", "shaq.ips");
	selNED->addItem("Stupid Sexy Flanders", "flanders.ips");
	selNED->addItem("Territorial Oak", "tree.ips");
	selNED->addItem("Thomas the Tank Engine", "thomas.ips");
	selNED->addItem("Yiazmat", "yiazmat.ips");

	layMain->addWidget(txtROM, 0, 0);
	layMain->addWidget(btnROM, 0, 1);
	layMain->addWidget(txtMode, 1, 0);
	layMain->addWidget(selMode, 1, 1);
	layMain->addWidget(txtPortraits, 2, 0);
	layMain->addWidget(chkPortraits, 2, 1);
	layMain->addWidget(txtSound, 3, 0);
	layMain->addWidget(chkSound, 3, 1);
	layMain->addWidget(txtSeed, 4, 0);
	layMain->addWidget(numSeed, 4, 1);
	layMain->addWidget(txtNED, 5, 0);
	layMain->addWidget(selNED, 5, 1);
	layMain->addWidget(btnSave, 6, 1);
}

void Exdeath::initInnates(void) {
	layInnates = new QVBoxLayout(this);
	grpInnates = new QGroupBox("Innate abilities");
	grpInnates->setLayout(layInnates);
	layColumn2->addWidget(grpInnates);

	chkPassages = new QCheckBox("Innate Passages");
	chkPitfalls = new QCheckBox("Innate Pitfalls");
	chkLiteStep = new QCheckBox("Innate Light Step");
	chkDash     = new QCheckBox("Innate Dash");
	chkLearning = new QCheckBox("Innate Learning");
	layInnates->addWidget(chkPassages);
	layInnates->addWidget(chkPitfalls);
	layInnates->addWidget(chkLiteStep);
	layInnates->addWidget(chkDash);
	layInnates->addWidget(chkLearning);
}

void Exdeath::initMulti(void) {
	grpMulti = new QGroupBox("Multipliers");
	layMulti = new QFormLayout(this);
	grpMulti->setLayout(layMulti);
	layColumn2->addWidget(grpMulti);

	layXP = new QHBoxLayout(this);
	butsXP = new QButtonGroup();
	layAP = new QHBoxLayout(this);
	butsAP = new QButtonGroup();
	layGil = new QHBoxLayout(this);
	butsGil = new QButtonGroup();

	int i[4] = {1, 2, 4, 8};
	for (int j = 0; j < 4; j++) {
		char temp[2];
		snprintf(temp, 2, "%dx", i[j]);
		radXP[j] = new QRadioButton(temp);
		radAP[j] = new QRadioButton(temp);
		radGil[j] = new QRadioButton(temp);
		butsXP->addButton(radXP[j]);
		butsXP->setId(radXP[j], i[j]);
		butsAP->addButton(radAP[j]);
		butsAP->setId(radAP[j], i[j]);
		butsGil->addButton(radGil[j]);
		butsGil->setId(radGil[j], i[j]);
		layXP->addWidget(radXP[j]);
		layAP->addWidget(radAP[j]);
		layGil->addWidget(radGil[j]);
	}
	radXP[0]->setChecked(true);
	radAP[0]->setChecked(true);
	radGil[0]->setChecked(true);
	layMulti->addRow("XP:", layXP);
	layMulti->addRow("AP:", layAP);
	layMulti->addRow("Gil:", layGil);
}

void Exdeath::initConfig(void) {
	QString temp = _cfg->value("rom/filename", "").toString();

	if (temp.length() != 0) {
		filename = temp;
	}
	selMode->setCurrentIndex(_cfg->value("main/mode", 0).toInt());
	selNED->setCurrentIndex(_cfg->value("main/ned", 1).toInt());
	chkPortraits->setChecked(_cfg->value("main/portraits", false).toBool());
	chkSound->setChecked(_cfg->value("main/sound_restore", false).toBool());

	chkPassages->setChecked(_cfg->value("innate/passages", false).toBool());
	chkPitfalls->setChecked(_cfg->value("innate/pitfalls", false).toBool());
	chkLiteStep->setChecked(_cfg->value("innate/litestep", false).toBool());
	chkDash->setChecked(_cfg->value("innate/dash", false).toBool());
	chkLearning->setChecked(_cfg->value("innate/learning", false).toBool());

	butsXP->button(_cfg->value("multi/xp", 1).toInt())->setChecked(true);
	butsAP->button(_cfg->value("multi/ap", 1).toInt())->setChecked(true);
	butsGil->button(_cfg->value("multi/gil", 1).toInt())->setChecked(true);
}

void Exdeath::btnSave_clicked(bool trigger) {
	_cfg->setValue("rom/filename", filename);
	_cfg->setValue("main/mode", selMode->currentIndex());
	_cfg->setValue("main/ned", selNED->currentIndex());
	_cfg->setValue("main/portraits", chkPortraits->isChecked());
	_cfg->setValue("main/sound_restore", chkSound->isChecked());

	_cfg->setValue("innate/passages", chkPassages->isChecked());
	_cfg->setValue("innate/pitfalls", chkPitfalls->isChecked());
	_cfg->setValue("innate/litestep", chkLiteStep->isChecked());
	_cfg->setValue("innate/dash", chkDash->isChecked());
	_cfg->setValue("innate/learning", chkLearning->isChecked());

	_cfg->setValue("multi/xp", butsXP->checkedId());
	_cfg->setValue("multi/ap", butsAP->checkedId());
	_cfg->setValue("multi/gil", butsGil->checkedId());
	_cfg->sync();
}

void Exdeath::btnROM_clicked(bool trigger) {
	filename = QFileDialog::getOpenFileName(
		this,
		"Select ROM image",
		QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation)[0],
		"GBA ROM images (*.gba)"
	);
	_cfg->setValue("rom/filename", filename);
	QFile *target = new QFile(filename);
	QCryptographicHash *md5 = new QCryptographicHash(QCryptographicHash::Md5);
	target->open(QIODevice::ReadOnly);
	if (md5->addData(target)) {
		if (md5->result().toHex().compare("9ed82843cc54876362be56faccb15d75") != 0) {
			error->showMessage("You must provide a Final Fantasy V Advance US image.");
		}
	}
	target->close();
}
void Exdeath::btnApply_clicked(bool trigger) {
	if (filename == nullptr) {
		error->showMessage("You can't apply patches without a ROM.");
		return;
	}
	QFile *target;
	QStringList patches;
	QString output = QFileDialog::getSaveFileName(
		this,
		"Select target ROM image",
		QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation)[0],
		"GBA ROM images (*.gba)"
	);
	QFile::copy(filename, output);
	int mode = selMode->currentIndex();
	std::mt19937 rand(numSeed->value());
	std::uniform_int_distribution<> dist(1, selNED->count() - 1);

	if (mode > 0) {
		patches << ":/patches/" + selMode->itemData(mode).toString();
	}
	if (chkPortraits->isChecked()) {
		patches << ":/patches/portraits.ips";
	}
	if (chkSound->isChecked()) {
		patches << ":/patches/sound_restoration.ips";
	}
	int idx = selNED->currentIndex();
	if (idx == 0) {
		idx = dist(rand);
	}
	if ((idx == 1) && ((mode > 2) && (mode < 5))) {
		error->showMessage("You can't set a custom NED with this mode; it'll break.");
		return;
	}
	if (idx > 1) {
		patches << ":/patches/ned/" + selNED->itemData(idx).toString();
	}
	char *XP = butsXP->checkedButton()->text().toLatin1().data();
	if (strncmp(XP, "1", 2)) {
		QString temp = ":/patches/xp/";
		temp.append(XP);
		temp.append("x.ips");
		patches << temp.toLatin1().data();
	}
	char *AP = butsAP->checkedButton()->text().toLatin1().data();
	if (strncmp(AP, "1", 2)) {
		QString temp = ":/patches/ap/";
		temp.append(AP);
		temp.append("x.ips");
		patches << temp.toLatin1().data();
	}
	char *Gil = butsGil->checkedButton()->text().toLatin1().data();
	if (strncmp(Gil, "1", 2)) {
		QString temp = ":/patches/gil/";
		temp.append(Gil);
		temp.append("x.ips");
		patches << temp.toLatin1().data();
	}

	target = new QFile(output);
	target->open(QIODevice::ReadWrite);
	if (patches.size() > 0) {
		for (int i = 0; i < patches.size(); i++) {
			QFile *patch = new QFile(patches[i]);
			patch->open(QIODevice::ReadOnly);
			applyPatch(target, patch);
		}
	}

	bool global_innates = (chkPassages->isChecked() || chkPitfalls->isChecked() || chkLiteStep->isChecked() || chkDash->isChecked() || chkLearning->isChecked());
	if (mode == 1) {
		Randomizer *rando = new Randomizer(rand);
		QFile *pfile = new QFile(output + ".ips");
		pfile->open(QIODevice::WriteOnly);
		QBuffer *patch = rando->makeRandom(global_innates);
		pfile->write(patch->readAll());
		patch->seek(0);
		pfile->close();
		applyPatch(target, patch);
	}
	if (global_innates) {
		applyInnates(target);
	}
	target->close();
}

void Exdeath::applyPatch(QFile *file, QIODevice *data) {
	// skipping header
	data->seek(5);

	while (!data->atEnd()) {
		unsigned int seek = 0;
		unsigned short length = 0;
		char temp[65536];

		data->read(temp, 3);
		if (!strncmp(temp, "EOF", 3)) {
			break;
		}

		seek = ((temp[0] & 0xff) << 16) + ((temp[1] & 0xff) << 8) + (temp[2] & 0xff);
		file->seek(seek);
		data->read(temp, 2);
		length = ((temp[0] & 0xff) << 8) + (temp[1] & 0xff);

		if (length == 0) {
			// RLE hunk
			data->read(temp, 2);
			length = ((temp[0] & 0xff) << 8) + (temp[1] & 0xff);
			data->read(temp, 1);

			for (unsigned int i = 0; i < length; i++) {
				file->write(temp, 1);
			}
		} else {
			data->read(temp, length);
			file->write(temp, length);
		}
	}

	file->flush();
	data->close();
}
void Exdeath::applyInnates(QFile *file) {
	unsigned char base = 0;
	int mode = selMode->currentIndex();

	if (mode > 1) {
		error->showMessage("You must use Base or Unlocked Jobs to use these options.");
		return;
	}

	if (chkPassages->isChecked()) base |= Job::Passages;
	if (chkPitfalls->isChecked()) base |= Job::Pitfalls;
	if (chkLiteStep->isChecked()) base |= Job::LiteStep;
	if (chkDash->isChecked())     base |= Job::Dash;
	if (chkLearning->isChecked()) base |= Job::ILearning;

	for (int i = 0; i < 26; i++) {
		char temp[2];
		file->seek(job_innates + (i * 2));
		file->read(temp, 2);
		temp[0] |= base;
		file->seek(job_innates + (i * 2));
		file->write(temp, 2);
	}
}
