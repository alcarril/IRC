/* ************************************************************************** */ // CAMBIOS
/*                                                                            */ // CAMBIOS
/*                                                        :::      ::::::::   */ // CAMBIOS
/*   FileTransfer.cpp                                   :+:      :+:    :+:   */ // CAMBIOS
/*                                                    +:+ +:+         +:+     */ // CAMBIOS
/*   By: Guille <Guille@student.42.fr>              +#+  +:+       +#+        */ // CAMBIOS
/*                                                +#+#+#+#+#+   +#+           */ // CAMBIOS
/*   Created: 2026/06/19 12:00:00 by Guille            #+#    #+#             */ // CAMBIOS
/*   Updated: 2026/06/19 12:00:00 by Guille           ###   ########.fr       */ // CAMBIOS
/*                                                                            */ // CAMBIOS
/* ************************************************************************** */ // CAMBIOS
// CAMBIOS
#include "FileTransfer.hpp" // CAMBIOS
#include "Client.hpp" // CAMBIOS
#include <sys/socket.h> // CAMBIOS
#include <sys/stat.h> // CAMBIOS
#include <iostream> // CAMBIOS
// CAMBIOS
FileTransfer::FileTransfer(int id, Client* sender, Client* receiver, // CAMBIOS
							const std::string& filename, const std::string& filepath) // CAMBIOS
	: _id(id), // CAMBIOS
	  _sender(sender), // CAMBIOS
	  _receiver(receiver), // CAMBIOS
	  _filename(filename), // CAMBIOS
	  _filepath(filepath), // CAMBIOS
	  _state(PENDING), // CAMBIOS
	  _fileSize(0), // CAMBIOS
	  _bytesSent(0) // CAMBIOS
{ // CAMBIOS
	struct stat st; // CAMBIOS
	if (stat(filepath.c_str(), &st) == 0) // CAMBIOS
		_fileSize = static_cast<long>(st.st_size); // CAMBIOS
} // CAMBIOS
// CAMBIOS
FileTransfer::~FileTransfer() // CAMBIOS
{ // CAMBIOS
	if (_file.is_open()) // CAMBIOS
		_file.close(); // CAMBIOS
} // CAMBIOS
// CAMBIOS
int FileTransfer::getId() const // CAMBIOS
{ // CAMBIOS
	return _id; // CAMBIOS
} // CAMBIOS
// CAMBIOS
Client* FileTransfer::getSender() const // CAMBIOS
{ // CAMBIOS
	return _sender; // CAMBIOS
} // CAMBIOS
// CAMBIOS
Client* FileTransfer::getReceiver() const // CAMBIOS
{ // CAMBIOS
	return _receiver; // CAMBIOS
} // CAMBIOS
// CAMBIOS
std::string FileTransfer::getFilename() const // CAMBIOS
{ // CAMBIOS
	return _filename; // CAMBIOS
} // CAMBIOS
// CAMBIOS
std::string FileTransfer::getFilepath() const // CAMBIOS
{ // CAMBIOS
	return _filepath; // CAMBIOS
} // CAMBIOS
// CAMBIOS
TransferState FileTransfer::getState() const // CAMBIOS
{ // CAMBIOS
	return _state; // CAMBIOS
} // CAMBIOS
// CAMBIOS
long FileTransfer::getFileSize() const // CAMBIOS
{ // CAMBIOS
	return _fileSize; // CAMBIOS
} // CAMBIOS
// CAMBIOS
long FileTransfer::getBytesSent() const // CAMBIOS
{ // CAMBIOS
	return _bytesSent; // CAMBIOS
} // CAMBIOS
// CAMBIOS
bool FileTransfer::openFile() // CAMBIOS
{ // CAMBIOS
	if (_file.is_open()) // CAMBIOS
		return true; // CAMBIOS
	_file.open(_filepath.c_str(), std::ios::binary); // CAMBIOS
	return _file.is_open(); // CAMBIOS
} // CAMBIOS
// CAMBIOS
void FileTransfer::setState(TransferState state) // CAMBIOS
{ // CAMBIOS
	_state = state; // CAMBIOS
} // CAMBIOS
// CAMBIOS
int FileTransfer::sendChunk(int receiverFd) // CAMBIOS
{ // CAMBIOS
	if (!_file.is_open()) // CAMBIOS
		return -1; // CAMBIOS
// CAMBIOS
	char buf[1024]; // CAMBIOS
	_file.read(buf, sizeof(buf)); // CAMBIOS
	int bytes = static_cast<int>(_file.gcount()); // CAMBIOS
	if (bytes > 0) // CAMBIOS
	{ // CAMBIOS
		int sent = send(receiverFd, buf, bytes, 0); // CAMBIOS
		if (sent > 0) // CAMBIOS
			_bytesSent += sent; // CAMBIOS
		return sent; // CAMBIOS
	} // CAMBIOS
	if (_file.eof()) // CAMBIOS
	{ // CAMBIOS
		_state = DONE; // CAMBIOS
		_file.close(); // CAMBIOS
	} // CAMBIOS
	return 0; // CAMBIOS
} // CAMBIOS
// CAMBIOS
void FileTransfer::closeFile() // CAMBIOS
{ // CAMBIOS
	if (_file.is_open()) // CAMBIOS
		_file.close(); // CAMBIOS
} // CAMBIOS
