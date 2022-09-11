module.exports = {
  types: [
    { value: 'feat', name: 'feat:     新增一个 feature' },
    { value: 'fix', name: 'fix:      修复 bug' },
    { value: 'docs', name: 'docs:     仅仅修复了文档' },
    {
      value: 'style',
      name: 'style:    仅仅修改了空格、格式缩进、逗号等等，不改变代码逻辑',
    },
    {
      value: 'refactor',
      name: 'refactor: 代码重构，没有加新功能或者修复 bug',
    },
    {
      value: 'perf',
      name: 'perf:     优化相关，比如提升性能、体验',
    },
    { value: 'test', name: 'test:     测试用例，包括单元测试、集成测试等' },
    {
      value: 'chore',
      name: 'chore:    对构建过程或辅助工具的更改\n            以及诸如文档生成之类的库',
    },
    { value: 'revert', name: 'revert:   回滚到一个 commit' },
    { value: 'WIP', name: 'WIP:      正在进行的工作' },
    { value: 'release', name: 'release:  发布一个新的版本或者tag' },
  ],

  scopes: [
    { name: 'accounts' },
    { name: 'admin' },
    { name: 'exampleScope' },
    { name: 'changeMe' },
    { name: 'git' },
  ],

  usePreparedCommit: false, // to re-use commit from ./.git/COMMIT_EDITMSG
  allowTicketNumber: false,
  isTicketNumberRequired: false,
  ticketNumberPrefix: 'TICKET-',
  ticketNumberRegExp: '\\d{1,5}',

  // it needs to match the value for field type. Eg.: 'fix'
  /*
  scopeOverrides: {
    fix: [
      {name: 'merge'},
      {name: 'style'},
      {name: 'e2eTest'},
      {name: 'unitTest'}
    ]
  },
  */
  // override the messages, defaults are as follows
  messages: {
    type: '请选择你要提交的类型:',
    scope: '\n请输入你修改的范围 (可选):',
    // used if allowCustomScopes is true
    customScope: '表示此更改的范围:',
    subject: '请简要描述提交 (必填):\n',
    body: '请输入详细描述提交 (可选).使用 "|" 启用新行:\n',
    breaking: '列出所有中断的更改 (可选):\n',
    footer: '列出此更改关闭的所有问题 (可选). E.g.: #31, #34:\n',
    confirmCommit: '是否确实要继续执行上述提交 ?',
  },

  allowCustomScopes: true,
  allowBreakingChanges: ['feat', 'fix'],
  // skip any questions you want
  skipQuestions: ['scope', 'body'],

  // limit subject length
  subjectLimit: 100,
  // breaklineChar: '|', // It is supported for fields body and footer.
  // footerPrefix : 'ISSUES CLOSED:'
  // askForBreakingChangeFirst : true, // default is false
}
