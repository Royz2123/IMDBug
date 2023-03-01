import * as vscode from 'vscode';
import { subscribeToDocumentChanges, refreshDocumentNow } from './diagnostics';

export function activate(context: vscode.ExtensionContext) {

	const diagnosticsCollection = vscode.languages.createDiagnosticCollection("imdbug");
	context.subscriptions.push(diagnosticsCollection);

	subscribeToDocumentChanges(context, diagnosticsCollection);

	const activateCommand = vscode.commands.registerCommand('imdbug.activate', () => {
		vscode.window.showInformationMessage('imdbug started working');
	});
	context.subscriptions.push(activateCommand);

	const refreshCommand = vscode.commands.registerCommand('imdbug.refresh', () => {
		refreshDocumentNow(diagnosticsCollection);
	});
	context.subscriptions.push(refreshCommand);
}

export function deactivate() {}
